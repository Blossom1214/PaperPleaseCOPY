#pragma once
#include "DrawCommand.h"
#include <vector>
#include <memory>
namespace Gdiplus {
    class Graphics;
}
class StaticVisualLayer {
public:
    void Add(std::unique_ptr<DrawCommand> cmd);
    const std::vector<std::unique_ptr<DrawCommand>>& GetCommands() const;
    void Clear();
private:
    std::vector<std::unique_ptr<DrawCommand>> _staticLalyerCommandsList;
};
