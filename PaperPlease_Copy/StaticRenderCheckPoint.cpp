#include "StaticRenderCheckPoint.h"
#include "RenderManager.h"
#include "framework.h"
using namespace std;
using namespace Gdiplus;
void InitStaticRenderLayer (ImageResource*imgRes)
{
    if (imgRes) {
        auto cmd = make_unique<DrawImageCommand>(
            imgRes->img.get(), imgRes->pos.x, imgRes->pos.y,
            static_cast<int>(imgRes->img->GetWidth() * imgRes->scaleX),
            static_cast<int>(imgRes->img->GetHeight() * imgRes->scaleY)
        );
        RenderManager::GetInstance().GetStaticLayer().Add(move(cmd));
    }

}