#pragma once
#include "IPlaybackPolicy.h"
class LoopPolicy : public IPlaybackPolicy
{
public:
	void AdvanceFrame(int& frameIndex, int sequenceSize, float& elapsedTime, bool& playing)override
	{
		frameIndex++;
		if (frameIndex >= sequenceSize)
			frameIndex = 0;

	}
};