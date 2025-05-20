#pragma once
#define NOMINMAX
#include <windows.h>
#include <gdiplus.h>
#include "PMath.h"
class GameObject
{
public:
    virtual void Update(float dt) = 0;//업데이트시간
    virtual void Render(Gdiplus::Graphics* g) = 0;//렌더(레이어에 밀어넣기)
    virtual ~GameObject() = default;//소멸자

    void SetPosition(const Vector2& pos);//위치설정
    const Vector2& GetPosition() const;//위치얻기
protected:
    Vector2 _position;
};

