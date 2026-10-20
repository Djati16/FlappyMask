#include "Rectangle.h"
#include <iostream>
#include "Window.h"
#include "MyMotor/Camera.h"
#include "MyLib/Sprite.h"

Rectangle::Rectangle(Vector2 pos, Vector2 scale, Vector2 origin, int tag) : Entity(pos, scale, origin)
{
	_rect = { _pos.GetX(), _pos.GetY(), _scale.GetX(), _scale.GetY() };
	_sprite = new Sprite(_pos, _scale, _origin);

}

void Rectangle::OnInitialize()
{
}

void Rectangle::SetSprite(Window& window, const char* asset)
{
	_sprite->LoadUniqueImage(window, asset);

}

void Rectangle::OnUpdate(float deltatime)
{
	UpdateAngleDegree(_velocityY, deltatime);
}

void Rectangle::OnEnd()
{
}
void Rectangle::UpdateAngleDegree(float posY, float deltatime)
{

	float rotationSpeed = 360.0f;

	if (posY <= 0)
	{
		_angle = -45.0f;
	}
	else
	{
		_angle += rotationSpeed * deltatime;
		if (_angle > 45.0f)
			_angle = 45.0f;

	}

}
void Rectangle::DrawSprite(Window& window, Camera* camera)
{
	_sprite->SetScale(GetScale().GetX() , GetScale().GetY() );
	_sprite->SetPos(GetPos().GetX() + camera->GetPos().GetX(), GetPos().GetY() + camera->GetPos().GetY());
	_sprite->Draw(window, camera);
}

void Rectangle::Draw(Window& window, Camera* camera)
{

	Vector2 pos = GetPos();
	Vector2 scale = GetScale();

	if(camera && _isCamAffected)
	{
		_rect.x = pos.GetX() - camera->GetPos().GetX();
		_rect.y = pos.GetY() - camera->GetPos().GetY();
		_rect.w = scale.GetX();
		_rect.h = scale.GetY();
	}
	else
	{
		_rect.x = pos.GetX();
		_rect.y = pos.GetY();
		_rect.w = scale.GetX();
		_rect.h = scale.GetY();
	}


	SDL_Renderer* renderer = window.GetRenderer();
	if (!renderer) {
		std::cout << "ERREUR: Renderer invalide dans Rectangle::Draw" << std::endl;
		return;
	}

	SDL_SetRenderDrawColor(window.GetRenderer(),GetR(), GetG(), GetB(), GetA());
	SDL_RenderFillRectF(window.GetRenderer(), &_rect);
	//SDL_RenderDrawRectF(window.GetRenderer(), &_rect);
}
