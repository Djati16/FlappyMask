#pragma once
#include "StaticObject.h"
#include "RectCollider.h"
#include "MyLib/Collideable.h"

class Timer;
class Camera;
class Window;
class Sprite;
class Obstacle : public Collideable, public Entity
{
private:

	Sprite* _sprite = nullptr;
	Vector2 _direction = { 0, 0 };


public:
	Obstacle(Vector2 pos, Vector2 scale, Vector2 origin, int tag = -1);
	~Obstacle();
	void OnInitialize() override;
	void OnCollision(Collideable* other) override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;
	void MoveUpdate(float x, float y);
	void Draw(Window& window, Camera* _camera = nullptr) override;
	void SetSprite(Window& window, const char* asset) override;

};


