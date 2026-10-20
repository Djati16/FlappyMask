#include "BackGround.h"
#include "MyMotor/GameManager.h"

#define WIDTH 1000
#define HEIGHT 800

BackGround::BackGround(Vector2 pos, Vector2 scale, Vector2 origin, Window* window, GameManager* gameManager) : Sprite(pos, scale, origin)
{
	_gameManager = gameManager;
	_window = window;
	SetScale(WIDTH, HEIGHT);
	SetPos(0, 0);
}

void BackGround::OnInitialize()
{
	LoadUniqueImage(*_window, "jungle2.bmp");
}

void BackGround::OnUpdate(float deltatime)
{

	SetPos(-_gameManager->GetOffsetX(), 0);
	SetPos(-_gameManager->GetOffsetX() + WIDTH, 0);
	
}

void BackGround::OnEnd()
{
}
