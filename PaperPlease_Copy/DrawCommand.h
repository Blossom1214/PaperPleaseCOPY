#pragma once
namespace Gdiplus {
    class Graphics;
    class Image;
}

class DrawCommand
{
public:
    virtual ~DrawCommand() = default;
    virtual void Execute(Gdiplus::Graphics* g, float sx, float sy) = 0;
};

class DrawImageCommand : public DrawCommand {
public:
    // 전체 이미지 렌더용 생성자
    DrawImageCommand(Gdiplus::Image* img, int dstX, int dstY, int width, int height);

    // 스프라이트 시트 자르기용 생성자
    DrawImageCommand(Gdiplus::Image* img, int dstX, int dstY, int srcX, int srcY, int width, int height);

    void Execute(Gdiplus::Graphics* g, float sx, float sy) override;

private:
    Gdiplus::Image* _img;
    int _x, _y;         // 화면에 그릴 위치
    int _w, _h;         // 그릴 크기 or 자를 크기
    int _srcX, _srcY;   // 이미지 내 자를 위치
    bool _useSrcRect;   // 자르기 여부
};
