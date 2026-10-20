#include "Writer.h"

#include "Window.h"

void Writer::Initialize()
{
	TTF_Init();
}

void Writer::InitColor(int r, int g, int b)
{
	_color = { (unsigned char)r, (unsigned char)g,(unsigned char)b };
}

void Writer::LoadFont()
{
	_font = TTF_OpenFont("police3.ttf", 25);
}

void Writer::FreeFont()
{
	TTF_CloseFont(_font);
}

void Writer::Clean()
{
	SDL_DestroyTexture(_texture);
	SDL_FreeSurface(_surface);
	TTF_Quit();
}

void Writer::Write(const char* text, Window& window, float posX, float posY)
{
	if (_texture)
	{
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
	}

	_surface = TTF_RenderText_Solid(_font, text, _color);
	_texture = SDL_CreateTextureFromSurface(window.GetRenderer(), _surface );

	SDL_FreeSurface(_surface);
	_surface = nullptr;
	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(_texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { posX, posY, texW, texH };
	SDL_RenderCopy(window.GetRenderer(), _texture, NULL, &dstrect);
}

