#pragma once
class IPlaybackPolicy
{
public:
	virtual ~IPlaybackPolicy() = default;

	virtual void AdvanceFrame(int& frameIndex,int sequenceSize,float& elapsedTime,bool& playing) = 0;
};

