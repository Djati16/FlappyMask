#include "Camera.h"
#include "Game1/Player.h"
#include "SceneManager.h"
#include <iostream>
#include <cmath>
#define WIDTH 1000
#define HEIGHT 800

Camera::Camera(Vector2 pos, Vector2 scale, Vector2 origin) : Entity(pos, scale, origin)
{
	
}
void Camera::Draw(Window& window, Camera* _camera)
{
	//aaa
}

void Camera::Initialize(Player* player)
{
	_player = player;
}


void Camera::OnInitialize()
{
}


void Camera::OnUpdate(float deltatime)
{

	if (!_player) return;
	float zoomFactor = 1; // < 1 = zoom in (moins de pixels visibles), > 1 = zoom out
	float visibleWidth = WIDTH * zoomFactor;
	float visibleHeight = HEIGHT * zoomFactor;

	_CamX = (_player->GetPos().GetX() + _player->GetScale().GetX()) - visibleWidth / 2.f;
	_CamY = (_player->GetPos().GetY() + _player->GetScale().GetY()) - visibleHeight / 2.f;

	_rightBorder = _CamX + visibleWidth;
	_leftBorder = _CamX;
	_topBorder = _CamY;
	_botBorder = _CamY + visibleHeight;
	SetPos(_CamX,0);
}

void Camera::OnEnd()
{
}

