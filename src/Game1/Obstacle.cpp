#include "Obstacle.h"
#include <iostream>
#include "MyLib/Rectangle.h"
#include "MyLib/Sprite.h"
#include "MyMotor/Camera.h"
#define WIDTH 1000
#define HEIGHT 800

float HeightHigh = HEIGHT * 1 / 4;

Obstacle::Obstacle(Vector2 pos, Vector2 scale, Vector2 origin, int tag) :Entity(pos, scale, origin, tag)
{
}

Obstacle::~Obstacle()
{
	delete _sprite;
}

void Obstacle::OnInitialize()
{
	_appliedGravity = false;
	_rectCollider = new RectCollider(_pos, _scale, _origin);
	_show = true;
	_sprite = new Sprite(_pos, _scale, _origin);
	_rectCollider->SetOwner(this);
	_direction = { 0, 0 };
	_speed = 100;
}

void Obstacle::OnCollision(Collideable* other)
{

}

void Obstacle::OnUpdate(float deltatime)
{

}

void Obstacle::OnEnd()
{
}

void Obstacle::Draw(Window& window, Camera* _camera )
{
	if (GetTag() == 2 && _sprite->hasBeenLoaded() == false)
	{
		SetSprite(window, "tuyauHaut.bmp");
	}
	if (GetTag() == 3 && _sprite->hasBeenLoaded() == false)
	{
		SetSprite(window, "tuyauBas.bmp");
	}
	_rectCollider->SetPos(_pos.GetX(), _pos.GetY());
	_rectCollider->SetScale(_scale.GetX()+10, _scale.GetY());
	
	if (_show)
		_sprite->Draw(window, _camera);
}


void Obstacle::SetSprite(Window& window, const char* asset)
{
	
	switch(GetTag())
	{
	case 2: 
		_sprite->SetScale(GetScale().GetX() + 40, GetScale().GetY());
		_sprite->SetPos(GetPos().GetX() - 15, GetPos().GetY() + 10);
		_sprite->LoadUniqueImage(window, asset);
		break;

	case 3:
		_sprite->SetScale(GetScale().GetX() + 40, GetScale().GetY());
		_sprite->SetPos(GetPos().GetX() - 15, GetPos().GetY() -10 );
		_sprite->LoadUniqueImage(window, asset);
		break;
	}
	
}
