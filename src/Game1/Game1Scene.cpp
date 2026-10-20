#include "Game1Scene.h"
#include "Player.h"	
#include "Ground.h"
#include "RectCollider.h"
#include "Point.h"
#include "stdlib.h"
#include "LevelManager.h"
#include "SceneManager.h"

#define WIDTH 1000
#define HEIGHT 800

Game1Scene::Game1Scene()
{
	CreateEntity<Player>(Vector2(10, HEIGHT / 2), Vector2(30, 60), Vector2(0, 0))->OnInitialize();
	CreateEntity<Ground>(Vector2(0, HEIGHT / 2 + 40), Vector2(500, 20), Vector2(0, 0))->OnInitialize();
}

Game1Scene* Game1Scene::GetGame1Scene()
{
	return this;
}


