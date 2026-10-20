#include "Point.h"
#include "MyLib/Circle.h"
#include "MyLib/Sprite.h"
#include "MyMotor/RectCollider.h"
#include "MyMotor/CircleCollider.h"
#include "MyLib/Window.h"
#include "MyMotor/GameManager.h"
#include "Player.h"
#include "MyLib/SoundLector.h"
#include <iostream>


Point::Point(Vector2 pos, Vector2 scale, Vector2 origin, int tag) : Entity(pos, scale, origin, tag)
{
	SoundLector::GetInstance()->LoadLightMusic("point", "pointSound.wav");
	SoundLector::GetInstance()->SetChunkVolume("point", 10);
}

Point::~Point()
{
	delete _sprite;
	_appliedGravity = false;
}

void Point::OnInitialize()
{
	_appliedGravity = false;
	_rectCollider = new RectCollider(_pos, _scale, _origin);
	_sprite = new Rectangle(_pos, _scale, _origin);
	_rectCollider->SetOwner(this);
	_direction = { 0, 0 };
	_speed = 100;
	_show = false;
	SetTag(1);
}

void Point::OnEnd()
{
	_destroyed = true;
}

void Point::OnCollision(Collideable* other)
{
	if (other->GetCircleCollider()->GetOwner()->GetTag() == 0)
	{
		if (Player* player = dynamic_cast<Player*>(other))
		{
			SoundLector::GetInstance()->PlayLightMusic("point", 0);
			player->AddProgression(1);
			player->AddScore(1);
			OnEnd();
		}	
	}
}

void Point::OnUpdate(float deltatime)
{

}


void Point::Draw(Window& window, Camera* _camera)
{	if(_show)
		_sprite->Draw(window, _camera);
}
