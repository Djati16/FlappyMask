#pragma once

class RectCollider;
class CircleCollider;

class Collideable
{
protected:
	
	RectCollider* _rectCollider = nullptr;
	CircleCollider* _circleCollider = nullptr;
	CircleCollider* _circleCollider2 = nullptr;

public:
	virtual ~Collideable() = default;
	virtual void OnCollision(Collideable* other) = 0;
	RectCollider* GetRectCollider();
	CircleCollider* GetCircleCollider();
	
};

