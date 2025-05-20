#include "RenderManager.h"
#include "framework.h"
using namespace std;
using namespace Gdiplus;

void RenderManager::RenderAll(Graphics* g, float sx, float sy)
{
	for (const auto& cmd : _staticLayer.GetCommands())
		cmd->Execute(g, sx, sy);
	for (const auto& cmd : _dynamicLayer.GetCommands())
		cmd->Execute(g, sx, sy);
}

void RenderManager::ClearPerFrame()
{
	_staticLayer.Clear();
	_dynamicLayer.Clear();
}
	