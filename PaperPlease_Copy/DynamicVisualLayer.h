#pragma once
#include "DrawCommand.h"
#include <vector>
#include <memory>
namespace Gdiplus {
    class Graphics;
}
class DynamicVisualLayer
{
public:
    const std::vector<std::unique_ptr<DrawCommand>>& GetCommands() const;
    void Add(std::unique_ptr<DrawCommand> cmd);
    void Clear();
    

private:
    std::vector<std::unique_ptr<DrawCommand>> _dynamicLayerCommandsList;
};

