#include "Player.h"
#include <iostream>
#include "MyLib/Input.h"
#include "MyLib/Rectangle.h"
#include "MyLib/Sprite.h"
#include "MyMotor/CircleCollider.h"
#include "MyLib/Window.h"
#include "MyMotor/GameManager.h"
#include "Point.h"
#include "Ground.h"
#include <Obstacle.h>
#include "MyLib/SoundLector.h"
#include <fstream>
#include <functional>


#define WIDTH 1000
#define HEIGHT 800


Player::Player(Vector2 pos, Vector2 scale, Vector2 origin, int tag) : Entity(pos, scale, origin, tag)
{
	_appliedGravity = true;
	_maxY = GetPos().GetY() + 20;
	_minY = GetPos().GetY() - 20;
}

Player* Player::GetPlayer()
{
	return this;
}

Player::~Player()
{
	delete _sprite;
	delete _circleCollider;
	_appliedGravity = false;
	
}

void Player::SetSprite(Window& window, const char* asset)
{
	_sprite->SetScale(GetScale().GetX() + 5, GetScale().GetY() + 5);
	_sprite->LoadUniqueImage(window, asset);
	_show = true;
}

void Player::SetSprite(Window& window, std::initializer_list<const char*> assets)
{
	_sprite->SetScale(GetScale().GetX() + 5, GetScale().GetY() + 5);

	_sprite->LoadAnimatedImages(window, assets);

	_show = true;
}

void Player::SetWaitingState(int state)
{
	if (state <= 0)
		_waitingState = false;
	else
		_waitingState = true;
}

void Player::OnInitialize()
{
	_input = _input->Get();
	_sprite = new Sprite(_pos, _scale, _origin);
	_circleCollider = new CircleCollider(_pos, Vector2(70, 80), _origin);
	
	_sprite->SetOrigin(0.5f, 0.5f);

	_circleCollider->SetOwner(this);
	_circleCollider->EnableCollision();
	
	SoundLector::GetInstance()->Initialize();

	SoundLector::GetInstance()->LoadLightMusic("gameOver", "gameOverSound.wav");
	SoundLector::GetInstance()->SetChunkVolume("gameOver", 10);
	SoundLector::GetInstance()->LoadLightMusic("flySound", "wingSound1.wav");
	SoundLector::GetInstance()->SetChunkVolume("flySound", 10);

	_direction = { 0, 0 };
	_speed = 200;
	_velocityX = 1;
	SetTag(0);
}

void Player::OnCollision(Collideable* other)
{
	


	/*if (_rectCollider->_collidingLeftRight == true)
	{
		UpdateXPos(_circleCollider->_overlapX);
	}

	if (_rectCollider->_collidingTopBot == true)
	{
		UpdateYPos(_circleCollider->_overlapY);
		_isGrounded = true;

		if (_velocityY > 0) 
			_velocityY = 0;
	}
	*/
	switch (other->GetRectCollider()->GetOwner()->GetTag())
	{
	case 2:
	case 3:
	case 4:
	
		SoundLector::GetInstance()->PlayLightMusic("gameOver", 0);
		OnEnd();
		break;
	}
}

void Player::OnUpdate(float deltatime)
{
	_isGrounded = false;
	if (!_waitingState)
		Gravity(deltatime);
	
	_moveX = 0;
	_moveY = 0;
	_isFlying = false;
	if(_canMove)
		Move(deltatime);
		
	UpdatePos();
}

void Player::UpdatePos()
{
	_sprite->SetPos(GetPos().GetX() - 13, GetPos().GetY());
	_circleCollider->SetPos(GetPos().GetX() + GetScale().GetX() / 2, GetPos().GetY() + GetScale().GetY() / 2);
	
}

void Player::UpdateXPos(float x)
{
	float newPosX = GetPos().GetX() + x;
	SetPosX(newPosX);
	_circleCollider->SetPosX(newPosX);
}

void Player::UpdateYPos(float y)
{
	float newPosY = GetPos().GetY() + y;

	SetPosY(newPosY);
	_circleCollider->SetPosY(newPosY);

}

void Player::Move(float deltatime)
{
	_moveY += _velocityY * deltatime;
	_sprite->UpdateAnimation(_sprite->GetAngle());
	if (_input->IsKeyDown(KEYCODE_SPACE) || _input->IsMouseDown(0) || _input->IsMouseDown(2) || _input->IsKeyDown(KEYCODE_UP))
	{
		Fly();

	}

	if(!_waitingState)
	{
		_moveX += _velocityX * deltatime * _speed;
		_sprite->UpdateAngleDegree(_velocityY, deltatime);
		

	}
	
		
	if (_moveX != 0 || _moveY != 0) 
	{
		MoveUpdate(_moveX, _moveY);
	}
}

void Player::MooveInWaitingState()
{
	float actualX = GetPos().GetX();
	float actualY = GetPos().GetY();


	if (actualY <= _minY)
		_waitingHeight = 0.5;
	else if (actualY >= _maxY)
		_waitingHeight = -0.5;

	MoveUpdate(0, _waitingHeight);
}

void Player::Fly()
{
	_velocityY = -4.50 * (GetScale().GetX() + GetScale().GetY());
	_isFlying = true;
	SoundLector::GetInstance()->PlayLightMusic("flySound", 0);
}

void Player::OnEnd()
{
	_destroyed = true;
}

void Player::MoveUpdate(float x, float y)
{
	float newPosX = GetPos().GetX() + x;
	float newPosY = GetPos().GetY() + y;

	SetPos(newPosX , newPosY);
	_circleCollider->SetPos(newPosX, newPosY);
	
}



int Player::SaveHighScore(int score)
{
	int currentBest = LoadVerifiedHighScore(); 

	if (score > currentBest)
	{
		std::ofstream outFile("highscore.txt");
		outFile << score << "\n" << ComputeChecksum(score);
		outFile.close();
		return score;
	}
	return currentBest;
}


void Player::Draw(Window& window, Camera* _camera)
{

	if (!_sprite->hasBeenLoaded())
		SetSprite(window, {"Bird1.bmp", "Bird2.bmp", "Bird3.bmp"});
	
	if (_show)
		_sprite->Draw(window, _camera);
		
}

void Player::AddScore(int i)
{
	_score += i;
}

void Player::AddProgression(int i)
{
	_progression += i;
}