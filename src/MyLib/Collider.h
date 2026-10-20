#pragma once
#include "SDL.h"

class Collider
{
protected:
	SDL_FRect _rect;
	bool _isEnable = true;
	bool _collidingTopBot = false;
	bool _collidingLeftRight = false;
public:
	void EnableCollision();
	void DisableCollision();
};

