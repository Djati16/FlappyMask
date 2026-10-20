#pragma once
#include "MyLib\Collideable.h"
#include "MyLib\Entity.h"

class Circle;
class Sprite;
class Input;
class Window;
class Rectangle;
class GameManager;

class Point: public Collideable, public Entity
{
private:
	Rectangle* _sprite;

public:

	Point(Vector2 pos, Vector2 scale, Vector2 origin, int tag = -1);

	~Point();
	void OnInitialize() override;
	void OnEnd() override;
	void OnCollision(Collideable* other) override;
	void OnUpdate(float deltatime) override;
	void Draw(Window& window, Camera* _camera = nullptr) override;

	void UpdatePos();

};

