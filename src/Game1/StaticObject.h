#pragma once
#include "MyLib\Collideable.h"
#include "MyLib\Entity.h"
class Player;
class Rectangle;
class Camera;
class StaticObject: public Collideable, public Entity
{
private:
	Rectangle* _rectangle = nullptr;
	Player* player = nullptr;
	float _strengthY = 0;

public:
	StaticObject(Vector2 pos, Vector2 scale, Vector2 origin, int tag = -1);
	void OnInitialize() override;
	void OnCollision(Collideable* other) override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;
	void Draw(Window& window, Camera* _camera = nullptr) override;


};

