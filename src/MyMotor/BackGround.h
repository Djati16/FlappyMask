#pragma once
#include "MyLib/Sprite.h"
class Window;
class GameManager;

class BackGround : public Sprite
{
private:
	GameManager* _gameManager = nullptr;
	float _offsetX = 0.f;
	Window* _window = nullptr;

public:
	
	BackGround(Vector2 pos, Vector2 scale, Vector2 origin, Window* window, GameManager* gameManager);
	void OnInitialize() override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;

};

