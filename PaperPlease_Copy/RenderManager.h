#pragma once
#include <vector>

#include <memory>
#include "DrawCommand.h"
#include "StaticVisualLayer.h"
#include "DynamicVisualLayer.h"
class RenderManager// 오로지 렌더를 위한 매니저
{
public:
	static RenderManager& GetInstance() //싱글턴화 됨
	{
		static RenderManager instance;
		return instance;
	}
	StaticVisualLayer& GetStaticLayer() {return _staticLayer;}
	DynamicVisualLayer& GetDynamicLayer(){return _dynamicLayer;}
	void RenderAll(Gdiplus::Graphics* g, float sx = 1.0f, float sy = 1.0f);
	void ClearPerFrame();
public:
	static constexpr int BASE_WIDTH = 1280;
	static constexpr int BASE_HEIGHT = 720;
private:
	RenderManager() = default;
	~RenderManager() = default;
	RenderManager(const RenderManager&) = delete;
	RenderManager& operator=(const RenderManager&) = delete;
	
	StaticVisualLayer  _staticLayer;
	DynamicVisualLayer _dynamicLayer;//실시간레이어
	
};
