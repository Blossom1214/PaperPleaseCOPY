#pragma once
#include <chrono>
#include <thread>
class FrameRateManager
{
public:
    void Init(int targetFPS);
    void BeginFrame();
    void EndFrame();
    float GetDeltaTime() const { return _deltaTime; }
private:
    float _deltaTime = 0.0f;
    int _targetFPS = 60;
    std::chrono::steady_clock::time_point _frameStartTime;
};
