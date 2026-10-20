 #include "Sprite.h"
#include "SDL_image.h"
#include "SDL.h"
#include "Window.h"
#include "MyMotor/Camera.h"
#include <iostream>

Sprite::Sprite(Vector2 pos, Vector2 scale, Vector2 origin) : Entity(pos, scale, origin)
{
}

void Sprite::OnInitialize()
{
}

void Sprite::OnUpdate(float deltatime)
{
}

void Sprite::OnEnd()
{
	for (SDL_Texture* tex : _frames)
		SDL_DestroyTexture(tex);
	_frames.clear();
}


void Sprite::LoadUniqueImage(Window& window, const char* file)
{
	_tempsurface = IMG_Load(file);
	_uniqueTexture = SDL_CreateTextureFromSurface(window.GetRenderer(), _tempsurface);
	SDL_QueryTexture(_uniqueTexture, NULL, NULL, 0, 0);
	SDL_FreeSurface(_tempsurface);
	isLoaded = true;
}

void Sprite::LoadAnimatedImages(Window& window, std::initializer_list<const char*> files)
{
	for (const char* file : files)
	{
		SDL_Surface* surface = IMG_Load(file);
		if (!surface) continue;

		SDL_Texture* tex = SDL_CreateTextureFromSurface(window.GetRenderer(), surface);
		SDL_FreeSurface(surface);

		_frames.push_back(tex);
	}

	_isAnimated = !_frames.empty();
	_lastFrameTime = SDL_GetTicks();
	isLoaded = true;
}

void Sprite::UpdateAnimation(float vy)
{
	if (_frames.empty()) return;

	// Si l'oiseau monte (vient de sauter) → joue l'animation
	if (vy < 60)
	{
		Uint32 now = SDL_GetTicks();
		if (now - _lastFrameTime >= (Uint32)_frameDelay)
		{
			_currentFrame = (_currentFrame + 1) % (int)_frames.size();
			_lastFrameTime = now;
		}
	}
	else
	{
		// Tombe ou neutre → bloque sur la frame du milieu
		_currentFrame = _frames.size() / 2;  // frame neutre
	}
}
void Sprite::Draw(Window& window, Camera* _camera)
{
	if (_camera)
		dstrect = { (int)(GetPos().GetX() - _camera->GetPos().GetX()), (int)(GetPos().GetY() - _camera->GetPos().GetY()),(int)GetScale().GetX(), (int)GetScale().GetY() };
	else
		dstrect = { (int)GetPos().GetX(), (int)GetPos().GetY(),(int)GetScale().GetX(), (int)GetScale().GetY() };

	SDL_Point center = { dstrect.w / 2, dstrect.h / 2 };

	SDL_Texture* activeTex = nullptr;

	if (_isAnimated && !_frames.empty())
		activeTex = _frames[_currentFrame];
	else
		activeTex = _uniqueTexture;
	
	if (!activeTex) return;

	//SDL_RenderCopy(window.GetRenderer(), _texture, 0, &dstrect);
	SDL_RenderCopyEx(window.GetRenderer(), activeTex, 0, &dstrect, _angle, &center, SDL_FLIP_NONE);
}


bool Sprite::hasBeenLoaded()
{
	return isLoaded;
}

void Sprite::UpdateAngleDegree(float vY, float deltatime)
{
	float rotationSpeed = 400.0f;

	if (vY <= 0)
	{
		_angle = -45.0f;
	}
	else
	{
		_angle += rotationSpeed * deltatime;
		if (_angle > 70.0f)
			_angle = 70.0f;
	}
	
}