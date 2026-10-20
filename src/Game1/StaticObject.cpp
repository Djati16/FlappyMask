#include "StaticObject.h"
#include "MyLib\Rectangle.h"
#include "MyMotor\Camera.h"
#include "MyMotor\RectCollider.h"
#include <iostream>

StaticObject::StaticObject(Vector2 pos, Vector2 scale, Vector2 origin, int tag) : Entity(pos, scale, origin, tag)
{
}

void StaticObject::OnInitialize()
{
	_appliedGravity = false;
	_rectCollider = new RectCollider(_pos, _scale, _origin);

	SetPos(_pos.GetX(), _pos.GetY());
	_rectCollider->SetScale(_scale.GetX(), _scale.GetY());
	_rectCollider->SetOrigin(_origin.GetX(), _origin.GetY());
	_rectCollider->SetPos(_pos.GetX(), _pos.GetY());

	_rectangle = new Rectangle(_pos, _scale, _origin);
	_rectangle->SetScale(_scale.GetX(), _scale.GetY());
	_rectangle->SetOrigin(_origin.GetX(), _origin.GetY());
	_rectangle->SetPos(_pos.GetX(), _pos.GetY());
}

void StaticObject::OnCollision(Collideable* other)
{
}

void StaticObject::OnUpdate(float deltaTime)
{
}

void StaticObject::OnEnd()
{
}

void StaticObject::Draw(Window& window, Camera* _camera)
{
	_rectangle->Draw(window, _camera);
}