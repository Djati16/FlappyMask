#include "Vector2.h"
#include <math.h>

Vector2::Vector2(float x, float y)
{
	_x = x;
	_y = y;
}

float Vector2::GetDistance(Vector2 otherVect)
{
	float distanceX = (otherVect.GetX() - _x) * (otherVect.GetX() - _x);
	float distanceY = (otherVect.GetY() - _y) * (otherVect.GetY() - _y);
	float distance = sqrt(distanceX + distanceY);
	return distance;
}

void Vector2::InitX(float x)
{
	_x = x;
}
void Vector2::InitY(float y)
{
	_y = y;
}

float Vector2::GetX()
{
	return _x;
}
float Vector2::GetY()
{
	return _y;
}
