#define NOMINMAX
#include "Animator.h"
#include "LoopPolicy.h"
#include "OncePolicy.h"
#include "PingPongPolicy.h"

using namespace std;
void Animator::SetSequence(const AnimationSequence* sequence)
{
    _sequence = sequence;
    _currentFrameIndex = 0;
    _elapsedTime = 0.0f;
    _playing = true;
    switch (_sequence->playback)
    {
    case PlaybackType::LOOP:
        SetPlaybackPolicy(std::make_unique<LoopPolicy>());
        break;
    case PlaybackType::ONCE:
        SetPlaybackPolicy(std::make_unique<OncePolicy>());
        break;
    case PlaybackType::PINGPONG:
        SetPlaybackPolicy(std::make_unique<PingPongPolicy>());
        break;
    }
}

void Animator::Update(float deltaTime)
{
    if (!_sequence || !_playing || _sequence->frames.empty()|| !_policy) return;

    _elapsedTime += deltaTime;

    const auto& currentFrame = (*_sequence).frames[_currentFrameIndex];
    float frameDuration = currentFrame.duration;
    frameDuration = std::max(frameDuration, 0.0001f);
    while (_elapsedTime >= frameDuration)
    {
        _elapsedTime -= frameDuration;

            _policy->AdvanceFrame(
                _currentFrameIndex,
                static_cast<int>(_sequence->frames.size()),
                _elapsedTime,
                _playing
            );

        if (!_playing || _sequence->frames.empty())
            break;
        frameDuration = std::max(_sequence->frames[_currentFrameIndex].duration, 0.0001f);
       
    }
}

const RECT& Animator::GetCurrentRect() const
{
    if (_sequence && !_sequence->frames.empty())
        return (*_sequence).frames[_currentFrameIndex].rect;

    static RECT dummy = { 0, 0, 0, 0 };
    return dummy;
}

void Animator::Play() { _playing = true; }
void Animator::Pause() { _playing = false; }
void Animator::Stop()
{
    _playing = false;
    _currentFrameIndex = 0;
    _elapsedTime = 0.0f;
}


void Animator::SetPlaybackPolicy(unique_ptr<IPlaybackPolicy> policy)
{
    if (!policy)
        OutputDebugString(L"[Animator] PlaybackPolicy is nullptr!\n");
    _policy = move(policy);
}
