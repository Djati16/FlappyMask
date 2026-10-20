#include "Collideable.h"
#include "MyMotor/RectCollider.h"
#include "MyMotor/CircleCollider.h"


RectCollider* Collideable::GetRectCollider()
{
	return _rectCollider;
}

CircleCollider* Collideable::GetCircleCollider()
{
	return _circleCollider;
}



