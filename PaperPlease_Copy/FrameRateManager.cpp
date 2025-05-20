#include "FrameRateManager.h"
using namespace std;
void FrameRateManager::Init(int targetFPS)
{
    _targetFPS = targetFPS;
}

void FrameRateManager::BeginFrame()
{
    _frameStartTime = chrono::steady_clock::now();
}

void FrameRateManager::EndFrame()
{
    using namespace std::chrono;

    auto frameEndTime = steady_clock::now();
    _deltaTime = duration<float>(frameEndTime - _frameStartTime).count();

    auto elapsed = duration_cast<milliseconds>(frameEndTime - _frameStartTime).count();

    int frameDelay = 1000 / _targetFPS;
    if (elapsed < frameDelay)
    {
        this_thread::sleep_for(milliseconds(frameDelay - elapsed));
    }
}
