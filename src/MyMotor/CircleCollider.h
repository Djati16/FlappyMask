#pragma once
#include "MyLib/Circle.h"
#include "MyLib/Drawable.h"
#include "Collider.h"
#include "MyLib/Collideable.h"

class Vector2;

class CircleCollider : public Circle
{
private:
	Entity* _owner = nullptr;
	bool _isEnable = false;
	Vector2 _center;
	Vector2 _rectCenter;
	Vector2 _rectShape;
	Vector2 _circleDistance;
	float  _cornerDistance;
	bool _collidingTopBot = false;
	bool _collidingLeftRight = false;
	float newX = 0;

public:

	CircleCollider(Vector2 pos, Vector2 scale, Vector2 origin);
	void EnableCollision();
	void DisableCollision();
	bool IsCollidingRect(RectCollider* other);
	void RepulseCircle(RectCollider* other);
	void Draw(Window& window, Camera* camera = nullptr) override;
	bool IsCollidingCircle(CircleCollider* other);
	void SetOwner(Entity* owner) { _owner = owner; }
	Entity* GetOwner() { return _owner; }
	void Repulse(RectCollider* other);

};