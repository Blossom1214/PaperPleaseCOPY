#include "DynamicVisualLayer.h"
#include "framework.h"
using namespace std;
using namespace Gdiplus;
const vector<unique_ptr<DrawCommand>>& DynamicVisualLayer::GetCommands() const
{
    return _dynamicLayerCommandsList;
}
void DynamicVisualLayer::Add(unique_ptr<DrawCommand> cmd)
{
    _dynamicLayerCommandsList.emplace_back(move(cmd));
}
void DynamicVisualLayer::Clear()
{
    _dynamicLayerCommandsList.clear();
}