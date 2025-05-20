#include "DoubleBufferManager.h"
using namespace std;
using namespace Gdiplus;
DoubleBufferManager::DoubleBufferManager(){}
DoubleBufferManager::~DoubleBufferManager(){}

void DoubleBufferManager::Initialize(HWND hwnd)
{
	RECT rt;
	GetClientRect(hwnd, &rt);
	_width = rt.right - rt.left;
	_height = rt.bottom - rt.top;

	_backBuffer=make_unique<Bitmap>(_width, _height, PixelFormat32bppARGB);
	_backGraphics = make_unique<Graphics>(_backBuffer.get());
}

void DoubleBufferManager::Resize(int width, int height)
{
	_width = width;
	_height = height;

	_backBuffer = make_unique<Bitmap>(_width, _height, PixelFormat32bppARGB);
	_backGraphics = make_unique<Graphics>(_backBuffer.get());
}

void DoubleBufferManager::Clear(const Color& color)
{
	if (_backGraphics)
		_backGraphics->Clear(color);
}

Graphics* DoubleBufferManager::GetGraphics()
{
	return _backGraphics.get();
}

void DoubleBufferManager::Present(HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	Graphics frontGraphics(hdc);
	
	frontGraphics.DrawImage(_backBuffer.get(), 0, 0);
	ReleaseDC(hwnd, hdc);
}
