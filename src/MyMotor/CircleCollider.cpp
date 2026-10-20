#include "CircleCollider.h"
#include "RectCollider.h"
#include "Collider.h"
#include <iostream>
#include "Window.h"
#include <cmath>



CircleCollider::CircleCollider(Vector2 pos, Vector2 scale, Vector2 origin) : Circle(pos, scale, origin)
{

	Circle::SetScale(scale.GetX()- 10, scale.GetY());
	SetOrigin(0.5f, 0.5f);
	_show = true;
}

void CircleCollider::Draw(Window& window, Camera* camera)
{
	if(_show)
		Circle::Draw(window, camera);
}

bool CircleCollider::IsCollidingCircle(CircleCollider* other)
{
	if (_isEnable)
	{
		if (other != this)
		{
	
			other->SetOrigin(0.5f, 0.5f);

			float radius1 = GetScale().GetX() / 2;
			float radius2 = other->GetScale().GetX() / 2;

			float distance = GetPos().GetDistance(other->GetPos());

			return distance <= (radius1 + radius2);
		}		
	}
	return false;
}

bool CircleCollider::IsCollidingRect(RectCollider* other)
{
	
	if (_isEnable)
	{
		if (!_isEnable || !other)
			return false;
	
		// Cercle
		float cx = GetPos().GetX();
		float cy = GetPos().GetY();
		float radius = GetScale().GetX() / 2;

		// Rectangle
		float rx = other->GetPos().GetX();
		float ry = other->GetPos().GetY();
		float rw = other->GetScale().GetX();
		float rh = other->GetScale().GetY();

		// Trouvez le point du rectangle le plus proche du centre du cercle
		float testX = cx;
		float testY = cy;

		// Quel bord est le plus proche ?
		if (cx < rx)         testX = rx;      // bord gauche
		else if (cx > rx + rw) testX = rx + rw;   // bord droit
		if (cy < ry)         testY = ry;      // bord haut
		else if (cy > ry + rh) testY = ry + rh;   // bord bas

		// Distance entre le centre du cercle et le point le plus proche
		float distX = cx - testX;
		float distY = cy - testY;
		float distance = sqrt((distX * distX) + (distY * distY));

		// Si la distance est inférieure au rayon, collision !
		return distance <= radius;
	}

	return false;
}

void CircleCollider::RepulseCircle(RectCollider* other)
{
	float dx = GetPos().GetX() - other->GetPos().GetX();
	float dy = GetPos().GetY() - other->GetPos().GetY();

	if (abs(dx) > abs(dy))
		_direction.InitX(-_direction.GetX());
	else
		_direction.InitY(-_direction.GetY());
}

void CircleCollider::EnableCollision()
{
	_isEnable = true;
}

void CircleCollider::DisableCollision()
{
	_isEnable = false;
}
