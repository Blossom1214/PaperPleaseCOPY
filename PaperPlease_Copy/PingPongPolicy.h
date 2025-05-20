#pragma once
#include "IPlaybackPolicy.h"
class PingPongPolicy : public IPlaybackPolicy
{
public:
	void AdvanceFrame(int& frameIndex, int sequenceSize, float& elapsedTime, bool& playing)override
	{
		if (sequenceSize <= 1) //애니메이션시퀀스사이즈가 1과같거나 작다면 애니메이션 프레임이 한개인것이므로 그냥 나감..
			return;
		if (_forward)//전방이라면?
		{
			frameIndex++;//한칸 인덱스를 늘리고
			if (frameIndex >= sequenceSize)//시퀀스사이즈랑 같아지거나 인덱스가 더크다는것은 곧 애니메이션프레임의 끝에 다다랐음을 알수잇음
			{
				frameIndex = sequenceSize - 2;//즉 그경우에는 현재의 값에 해당하는 인덱스에서 2를 빼야 현재값 -1 상태가되기때문에 이전상태로 돌아갈수가있고
				_forward = false;//이제 이것을 false로 바꾼상태에서 다시 이것이 반복문안에있기때문에 다시 만남

			}


		}
		else
		{
			frameIndex--; //여긴뭐..거꾸로 돌아가는거지..
			if (frameIndex < 0)
			{
				frameIndex = 1;
				_forward = true;

			}
		}

	}
private:
	bool _forward = true;
};