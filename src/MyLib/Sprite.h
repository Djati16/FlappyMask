#pragma once
#include "Entity.h"
#include "SDL.h"
#include <vector>

class Window;
class SDL_Surface;
class SDL_Texture;
class SDL_Rect;
class Camera;

class Sprite : public Entity
{
private:
	
	SDL_Rect dstrect;
	SDL_Surface* _tempsurface = nullptr;
	SDL_Texture* _uniqueTexture = nullptr;
	float _time = 0.01f;
	bool isLoaded = false;

	std::vector<SDL_Texture*> _frames;  // une texture par frame
	bool _isAnimated = false;
	int  _currentFrame = 0;
	int  _frameDelay = 200;
	Uint32 _lastFrameTime = 0;

public:
	Sprite(Vector2 pos, Vector2 scale, Vector2 origin);
	void Draw(Window& window, Camera* _camera = nullptr) override;
	void OnInitialize() override;
	void OnUpdate(float deltatime) override;
	void OnEnd() override;
	void UpdateAnimation(float vy);
	void LoadUniqueImage(Window& window, const char* file);
	void LoadAnimatedImages(Window& window, std::initializer_list<const char*> files);
	bool hasBeenLoaded();
	void UpdateAngleDegree(float vY, float deltatime);
	friend class Player;
};

