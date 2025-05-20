#include "DrawCommand.h"
#include "framework.h"
using namespace Gdiplus;

// 전체 이미지 or 단순 위치 지정용
DrawImageCommand::DrawImageCommand(Gdiplus::Image* img, int dstX, int dstY, int width, int height)
    : _img(img), _x(dstX), _y(dstY), _w(width), _h(height),
    _srcX(0), _srcY(0), _useSrcRect(false) {
}

// 스프라이트 시트 자르기용
DrawImageCommand::DrawImageCommand(Gdiplus::Image* img, int dstX, int dstY, int srcX, int srcY, int width, int height)
    : _img(img), _x(dstX), _y(dstY), _srcX(srcX), _srcY(srcY), _w(width), _h(height),
    _useSrcRect(true) {
}

void DrawImageCommand::Execute(Graphics* g, float sx, float sy)
{
    if (!_img) return;

    if (_useSrcRect)
    {
        g->DrawImage(
            _img,
            static_cast<INT>(_x * sx), static_cast<INT>(_y * sy),  // 화면에 그릴 위치
            _srcX, _srcY,                                           // 이미지 내 자를 위치
            _w, _h,                                                 // 자를 크기
            UnitPixel
        );
    }
    else
    {
        g->DrawImage(
            _img,
            static_cast<INT>(_x * sx),
            static_cast<INT>(_y * sy),
            static_cast<INT>(_w * sx),
            static_cast<INT>(_h * sy)
        );
    }
}
