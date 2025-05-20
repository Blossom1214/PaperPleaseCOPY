#pragma once
#include "IPlaybackPolicy.h"
class OncePolicy : public IPlaybackPolicy
{
public:
	void AdvanceFrame(int& frameIndex, int sequenceSize, float& elapsedTime, bool& playing)override
	{
		
		if (frameIndex < sequenceSize - 1)
		{
			frameIndex++;
		}
		else
		{
			playing = false;
			elapsedTime = 0.0f;
		}
			
	}
};