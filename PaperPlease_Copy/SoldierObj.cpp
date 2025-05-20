#include "SoldierObj.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "framework.h"
using namespace std;
using namespace Gdiplus;
SoldierObj::SoldierObj(const wstring& imageKey):_imageKey(imageKey)
{
	_animator = std::make_unique<Animator>();
	
	SetState(NPCState::IDLE);
}

void SoldierObj::Update(float dt)
{
	if (_animator)
		_animator->Update(dt);

	switch (_state)
	{
	case NPCState::IDLE:
		break;
	case NPCState::WALKING:

		if (_moving)
		{
			if (MoveTowardsTarget(dt))
			{
				_moving = false;
				SetState(NPCState::IDLE);
			}
		}
		break;
	case NPCState::TALKING:
		break;
	case NPCState::WAITING:
		break;
	case NPCState::LEAVING:
		break;
	case NPCState::FIGHTING:
		break;
	case NPCState::DIE:
		break;
	default:
		break;
	}
}

void SoldierObj::Render(Graphics* g)
{
	Animator* animator = GetAnimator();
	if (!animator)
		return;
	const RECT& frameRect = animator->GetCurrentRect();
	
	ImageResource* res = ResourceManager::GetInstance().GetImageResource(_imageKey);
	if (!res || !res->img)
		return;
	int drawX = static_cast<int>(_position.x);
	int drawY = static_cast<int>(_position.y);
	int drawW = frameRect.right - frameRect.left;
	int drawH = frameRect.bottom - frameRect.top;
		
	auto cmd = std::make_unique<DrawImageCommand>(res->img.get(), drawX, drawY,frameRect.left,frameRect.top, drawW, drawH);

	RenderManager::GetInstance().GetDynamicLayer().Add(move(cmd));
}

const AnimationSequence* SoldierObj::GetSequenceByState(NPCState state) const
{
	wstring aniKey;
	switch (state)
	{
	case NPCState::IDLE:
		aniKey = L"idle";
		break;
	case NPCState::WALKING:
		aniKey = L"walk";
		break;
	case NPCState::TALKING:
		aniKey = L"talk";
		break;
	case NPCState::WAITING:
		aniKey = L"wait";
		break;
	case NPCState::LEAVING:
		aniKey = L"leave";
		break;
	case NPCState::FIGHTING:
		aniKey = L"fight";
		break;
	case NPCState::DIE:
		aniKey = L"die";
		break;
	default:
		break;
	}
	return AnimationManager::GetInstance().Get(_imageKey,aniKey);
}
