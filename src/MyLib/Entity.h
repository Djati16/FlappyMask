#pragma once
#include "Vector2.h"
#include "Drawable.h"
#include "Transformable.h"
class Camera;
class Window;

class Entity : public Drawable, public Transformable
{
protected:

	Vector2 _direction;
	int _tag = -1;

	
	float _speed = 0.f;
	float gravity = 35;
	float gravityApplied;
	float _velocityY = 0.f;
	float _velocityX = 0.f;
	float _angle = 0.f;
	bool _isCamAffected = true;
	bool _entityInRange = false;
	bool _destroyed = false;
	bool _appliedGravity = true;
	bool _isGrounded = false;
	bool _canMove = true;
	bool _show = true;
public:

	Entity(Vector2 pos, Vector2 scale, Vector2 origin, int tag = -1);
	virtual ~Entity() = default;
	void Gravity(float deltatime);

	float GetGravityApplied();
	void SetTag(int a);
	int GetTag() { return _tag; };
	void SetRangeState(int i);
	void SetDestroyed();
	bool GetRangeState();
	float GetAngle();
	void SetCamAffected(const char* text);
	bool IsCamAffected() { return _isCamAffected; }
	virtual void OnInitialize() = 0;
	virtual void OnUpdate(float deltatime) = 0;
	virtual void OnEnd() = 0;
	virtual void SetSprite(Window& window, const char* asset);

	Vector2 GetDirection();
	
	bool IsDestroy();


};

