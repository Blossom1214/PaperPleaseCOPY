#include "GameObject.h"
void GameObject::SetPosition(const Vector2& pos)
{
	_position = pos;
}
const Vector2& GameObject::GetPosition() const
{
	return _position;
}