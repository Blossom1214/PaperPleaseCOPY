#pragma once
#include "framework.h"
namespace Gdiplus {
    class Graphics;

}
class BaseScene
{
public:
    virtual void Init() = 0;
    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
    virtual void Release() = 0;
    virtual ~BaseScene() = default;
};

