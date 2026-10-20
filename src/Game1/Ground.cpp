#include "Ground.h"
#include <iostream>
#include "MyLib/Rectangle.h"
#include "MyLib/Sprite.h"
#include "MyMotor/Camera.h"
#define WIDTH 1000
#define HEIGHT 800

Ground::Ground(Vector2 pos, Vector2 scale, Vector2 origin, int tag) :StaticObject(pos, scale, origin, tag)
{
}

Ground::~Ground()
{
	delete _sprite;
}

void Ground::OnInitialize()
{
	_rectCollider = new RectCollider(_pos, _scale, _origin);
	_sprite = new Rectangle(_pos, _scale, _origin);
	_show = false;
	_sprite->SetScale(_scale.GetX(), _scale.GetY());
	_sprite->SetOrigin(_origin.GetX(), _origin.GetY());
	_sprite->SetPos(_pos.GetX(), _pos.GetY());
	_rectCollider->SetOwner(this);
	_rectCollider->DisableCollision();
	_direction = { 0, 0 };
	SetTag(4);
}

void Ground::OnCollision(Collideable* entity)
{
}

void Ground::OnUpdate(float deltatime)
{
}

void Ground::Draw(Window& window, Camera* _camera)
{
	if(_show)
		_sprite->Draw(window, _camera);
}
