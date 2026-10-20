#pragma once
#include <SDL_ttf.h>
class Window;


class Writer
{

protected:
	SDL_Texture* _texture = nullptr;
	SDL_Color _color = { 0, 0, 0 };
	SDL_Surface* _surface = nullptr;
	TTF_Font* _font = nullptr;
	int _size = 25;
public:
	
	void Initialize();
	void InitColor(int r, int g, int b);
	void LoadFont();
	void FreeFont();
	void Clean();
	void Write(const char* text, Window& window ,float posX, float posY);
};

