#pragma once
#include "NpcObj.h"
#include <string>
namespace Gdiplus {
	class Graphics;
}
class SoldierObj : public NpcObj
{
public:
	SoldierObj(const std::wstring& imageKey);

	virtual void Update(float dt) override;
	virtual void Render(Gdiplus::Graphics* g) override;
	void StartWalkingTo(const Vector2& targetPos,float delay)
	{
		SetState(NPCState::WALKING);
		BeginMove(targetPos, delay);
	}
protected:
	//npc의 상태를 입력해주면 이제 그대로 시퀀스 키값을 반환해서 그 애니메이션을 애니메이터에게 넣게 되는과정
	virtual const AnimationSequence* GetSequenceByState(NPCState state) const override;
private:
	//리소스키
	std::wstring _imageKey;

};
//군인의 움직임 여부와
//군인들은 과연 어디서부터 어디까지 움직여야하는지?
//움직임에 관한 선형보간은 위에서 이미 하였음
//그럼 이제 해야하는건 선형보간된것을 활용해서