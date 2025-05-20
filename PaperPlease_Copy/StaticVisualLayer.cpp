#include "StaticVisualLayer.h"
#include "framework.h"
using namespace std;
using namespace Gdiplus;
void StaticVisualLayer::Add(unique_ptr<DrawCommand> cmd)
{
    _staticLalyerCommandsList.emplace_back(move(cmd));
}
const vector<unique_ptr<DrawCommand>>& StaticVisualLayer::GetCommands() const
{
    return _staticLalyerCommandsList;
}
void StaticVisualLayer::Clear()
{
    _staticLalyerCommandsList.clear();
}   