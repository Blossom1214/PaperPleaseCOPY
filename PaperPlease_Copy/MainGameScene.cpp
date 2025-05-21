#include "MainGameScene.h"
#include "StaticRenderCheckPoint.h"
#include "ResourceManager.h"
#include "DoubleBufferManager.h"
#include "RenderManager.h"
using namespace std;
using namespace Gdiplus;
extern DoubleBufferManager backBuffer;
void MainGameScene::Init()
{
    AddDayCount();
    
    InitStaticRenderLayer(ResourceManager::GetInstance().GetImageResource(L"CheckpointBack"));
    InitStaticRenderLayer(ResourceManager::GetInstance().GetImageResource(L"BoothWall"));
    InitStaticRenderLayer(ResourceManager::GetInstance().GetImageResource(L"Desk"));
    const AnimationSequence* seq = AnimationManager::GetInstance().Get(L"soldier", L"walk");
    if (_DayCount <= 2) {
        auto soldier = make_unique<SoldierObj>(L"soldier");
        soldier->GetAnimator()->SetSequence(seq);
        soldier->SetPosition({ 1100.0f, -100.0f });
        soldier->StartWalkingTo({ 1100.0f, 100.0f });
        _SoldierNpcs.emplace_back(move(soldier));
    }
    if (_DayCount == 3)
    {
        for (int i = 0; i < 5; ++i) {
            auto soldier = make_unique<SoldierObj>(L"soldier");
            soldier->GetAnimator()->SetSequence(seq);
            soldier->SetPosition({ 1100.0f, -100.0f });
            if (i > 2)
            {
                soldier->SetPosition({ 275.0f, -100.0f });
            }
            _SoldierNpcs.emplace_back(move(soldier));
        }
        _SoldierNpcs[0]->StartWalkingTo({1100.0f, 100.0f});
        _SoldierNpcs[1]->StartWalkingTo({1100.0f, 50.0f});
        _SoldierNpcs[2]->StartWalkingTo({1100.0f, 150.0f});
        _SoldierNpcs[3]->StartWalkingTo({275.0f, 100.0f});
        _SoldierNpcs[4]->StartWalkingTo({275.0f, 50.0f});
    }
}
void MainGameScene::Update(float dt)
{
    for (auto& npc : _SoldierNpcs)
    {
        npc->Update(dt);
    }
}
void MainGameScene::Render()
{
    for (auto& npc : _SoldierNpcs)
    {
        npc->Render(backBuffer.GetGraphics());
    }
}
void  MainGameScene::Release()
{
    _SoldierNpcs.clear();
    RenderManager::GetInstance().ClearPerFrame();
}