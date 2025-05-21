#include "NpcObj.h"
using namespace std;
bool NpcObj::MoveTowardsTarget(float dt)
{
    //목표까지의 거리가 0이면사실 이미 해당위치에 있는것
    if (_totalDistance <= 0.0f)
    {
        //해당위치에 있는것이니 해당위치를 포지션에 넣음
        _position = _targetPos;
        return true;    
    }
    //시간만큼 누적(경과시간)
    _elapsed += dt;
    if (!_moveStarted && _elapsed >= _delayTime)
    {
        _elapsed = 0.0f;                   
        _moveStarted = true;               
    }
    if (!_moveStarted)
        return false;
    //속도와 시간을 곱하여서 현재까지 이동한 거리를 계산
    float traveled = _moveSpeed * _elapsed;
    //전채분의 현재 진행률을 계산하여 저장함 최소값은 0에서 최대값은 1 즉 1을 넘어가지않게 잡아주는 역할을함
    float t = clamp(traveled / _totalDistance, 0.0f, 1.0f);
    //시작위치로부터의 선타겟위치까지의 선형보간을 통해 포지션을 계산함
    _position = _startPos.Lerp(_targetPos, t);
    //이제 b-a를하였을때 x의값이 0보다 크거나 같으면 우측값저장!
    SetDirection((_targetPos - _startPos).x >= 0.0f);
    //다 끝나고나서 진행률이 1과 동일하거나 넘어가면 참(사실 1이되면 도달한것)
    return(t >= 1.0f);

}
void NpcObj::BeginMove(const Vector2& to,float delay)
{
    //선형보간을위해 위치정보를 현재위치로 초기화 해주는함수
    _startPos = _position;
    _targetPos = to;
    _elapsed = 0.0f;
    _delayTime = delay;
    _moveStarted = false;
    _totalDistance = (_targetPos - _startPos).Length();
    _moving = true;
}
void NpcObj::SetState(NPCState state)
{
    _state = state;

    const AnimationSequence* seq = GetSequenceByState(state);
    if (seq)
    {
        _animator->SetSequence(seq);
        _animator->Play();
    }
}

void NpcObj::SetDirection(bool right)
{
    _facingRight = right;
}