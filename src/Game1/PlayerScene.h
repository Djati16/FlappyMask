#pragma once
#include "Scene.h"
class SceneManager;
class Window;
class Player;
class GameManager;

class PlayerScene : public Scene
{
public:
	PlayerScene(GameManager* gameManager);
	PlayerScene* GetPlayerScene();
	friend class LevelManager;
};

