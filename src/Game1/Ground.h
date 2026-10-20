#pragma once
#include "StaticObject.h"
#include "RectCollider.h"

class Camera;
class Ground :  public StaticObject
{
private:

	Rectangle* _sprite = nullptr;
	Vector2 _direction = { 0, 0 };


public:
	Ground(Vector2 pos, Vector2 scale, Vector2 origin, int tag = -1);
	~Ground();	
	void OnInitialize() override;
	void OnCollision(Collideable* other) override;
	void MoveUpdate(float x, float y);
	void OnUpdate(float deltatime) override;
	void Draw(Window& window, Camera* _camera = nullptr) override;

};


