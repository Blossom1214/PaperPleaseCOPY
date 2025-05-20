#pragma once
#define NOMINMAX 
#include <Windows.h>
#include <memory>
#include <gdiplus.h>
class DoubleBufferManager
{
public:
	DoubleBufferManager();
	~DoubleBufferManager();

	void Initialize(HWND hwnd);
	void Resize(int width, int height);
	void Clear(const Gdiplus::Color& color = Gdiplus::Color(255, 0, 0, 0));
	Gdiplus::Graphics* GetGraphics(); // 백버퍼 그래픽 객체 제공
	void Present(HWND hwnd);          // 화면에 출력
	void Release() { _backGraphics.reset(); _backBuffer.reset();}
private:
	std::unique_ptr<Gdiplus::Bitmap> _backBuffer;
	std::unique_ptr<Gdiplus::Graphics> _backGraphics;
	int _width=0;
	int _height=0;
};

