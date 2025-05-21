#pragma once
#include "GameObject.h"
#include "NPCState.h"
#include "Animator.h"
#include <memory>
#include <string>
class NpcObj : public GameObject
{
public:
	virtual void Update(float dt) override =0;
	virtual void Render(Gdiplus::Graphics* g) override = 0;
	void SetAnimator(std::unique_ptr<Animator> animator) { _animator = move(animator); }
	Animator* GetAnimator() const { return _animator.get(); }
	NPCState GetState()const { return _state; }
protected:
	//이동 함수
	bool MoveTowardsTarget(float dt);
	//현재의 상태를 셋팅해주는 함수
	void SetState(NPCState state);
	//오른쪽을 바라보는지?
	void SetDirection(bool right);
	/// 선형보간할 시작점의 위치를 초기화해주는 함수
	void BeginMove(const Vector2& to, float delay);
	// 시퀀스 선택
	virtual const AnimationSequence* GetSequenceByState(NPCState state) const = 0;
protected:
	// 이동 시작점
	Vector2								_startPos;           
	// 목표 위치
	Vector2								_targetPos;           
	//npc이동속도
	float								_moveSpeed = 50.0f;
	// 이동 경과 시간
	float								_elapsed = 0.0f;     
	// 목표까지의 전체 거리
	float								_totalDistance = 0.0f;
	//애니메이션의 좌우판단
	bool								_facingRight = true; 
	//fsm을 위한 상태보관용도로만듬
	NPCState							_state = NPCState::IDLE;
	//애니메이션을 실행할 대상을 지정함
	std::unique_ptr<Animator>			_animator;
	//움직임의 여부
	bool _moving = false;
	// 실제 걷기 시작 여부
	bool _moveStarted = false;
	//딜레이타임
	float _delayTime = 0.0f;
	
};
	
