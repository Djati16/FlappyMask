#pragma once
#include "MyMotor/Scene.h"

class Game1Scene : public Scene
{
public:
	Game1Scene();
	Game1Scene* GetGame1Scene();
	friend class LevelManager;
};

