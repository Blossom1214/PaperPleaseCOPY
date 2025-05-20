#pragma once
#include "AnimationManager.h"
#include <memory>
#include "IPlaybackPolicy.h"
#include <Windows.h>
class Animator
{
public:
	Animator() = default;

	void SetSequence(const AnimationSequence* seq);//시퀀스 설정과 상태초기화
	void Update(float deltaTime);//시간누적+프레임전환


	const RECT& GetCurrentRect() const;//현재 프레임의 잘라낸 사각형 반환
	const AnimationSequence* GetCurrentSequence() const { return _sequence; };//시퀀스 반환(읽기)

	void Play();//재생상태
	void Pause();//일시정지
	void Stop();//정지후 처음으로

	

	bool IsPlaying() const { return _playing; }//현재 실행상태인지 반환

	void SetPlaybackPolicy(std::unique_ptr<IPlaybackPolicy> policy);//어떤전략을 쓸까ㅣ?!

private:
	const AnimationSequence* _sequence = nullptr;//현재 재생중인 애니메이션

	int _currentFrameIndex =0;//현재 프레임인덱스
	float _elapsedTime = 0.0f;//누적시간(프레임전환)
	bool _playing = true; //일시정지/재생

	std::unique_ptr<IPlaybackPolicy> _policy;
};


