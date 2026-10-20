#include "PlayerScene.h"
#include "Player.h"	
#include "Ground.h"
#include "RectCollider.h"
#include "Point.h"
#include "stdlib.h"
#include "LevelManager.h"
#include "SceneManager.h"
#include "MyMotor/UI.h"
#include "Game1/Player.h"
#include <iostream>
#include "MyMotor/GameManager.h"
#include "MyMotor/BackGround.h"

#define WIDTH 1000
#define HEIGHT 800

PlayerScene::PlayerScene(GameManager* gameManager)
{
	
	CreateEntity<Player>(Vector2(0, HEIGHT / 2), Vector2(80, 60), Vector2(0, 0))->OnInitialize();
	CreateEntity<Ground>(Vector2(0, HEIGHT - 10 ), Vector2(WIDTH +1 , 5), Vector2(0, 0))->OnInitialize();
	CreateEntity<Ground>(Vector2(0,-250), Vector2(WIDTH + 1, 5), Vector2(0, 0))->OnInitialize();
}

PlayerScene* PlayerScene::GetPlayerScene()
{
	return this;
}


