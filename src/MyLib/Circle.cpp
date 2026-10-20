#include "Circle.h"
#include "SDL.h"
#include "Window.h"
#include "MyMotor/Camera.h"


Circle::Circle(Vector2 pos, Vector2 scale, Vector2 origin) : Entity(pos, scale, origin) 
{

}

void Circle::OnInitialize()
{
}

void Circle::OnUpdate(float deltatime)
{
}

void Circle::OnEnd()
{
}

void Circle::Draw(Window& window, Camera* camera)
{
	SDL_SetRenderDrawColor(window.GetRenderer(), GetR(), GetG(), GetB(), GetA());

	_precision = 150;
	_radius = GetScale().GetX() / 2;
	Vector2  selfOrigin = GetOrigin();
	Vector2 center = GetPos();
	SetOrigin(0.5f, 0.5f);


	if (!camera)
	{
		_centerX = center.GetX();
		_centerY = center.GetY();
	}
	else
	{
		 _centerX = center.GetX() - camera->GetPos().GetX();
		 _centerY = center.GetY() - camera->GetPos().GetY();
	}

	double perimeter = 2 * M_PI;
	double step = perimeter / _precision;

	float lastX = _radius * cos(0) + _centerX;
	float lastY = _radius * sin(0) + _centerY;

	for (int i = 1; i <= _precision; i++)
	{
		float currentX = _radius * cos(step * i) + _centerX;
		float currentY = _radius * sin(step * i) + _centerY;

		SDL_RenderDrawLine(window.GetRenderer(), lastX, lastY, currentX, currentY);

		lastX = currentX;
		lastY = currentY;
	}

	SetOrigin(selfOrigin.GetX(), selfOrigin.GetY());

}