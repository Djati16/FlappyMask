#include "Window.h"
#include "MyMotor/Scene.h"
#include "Input.h"
#include "Entity.h"
#include <iostream>
#include "MyMotor/Camera.h"
#include "MyMotor/RectCollider.h"
#include "MyMotor/CircleCollider.h"
#include "MyLib/Collideable.h"

Window::Window(const char* title, int x, int y, int w, int h, Uint32 flags)
{
	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_OPENGL| SDL_WINDOW_MOUSE_CAPTURE); //| SDL_WINDOW_INPUT_GRABBED
	_renderer = SDL_CreateRenderer(_window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_GetWindowSize(_window, &w, &h);
	SDL_Surface* icon = IMG_Load("MaskIcon.png");
	if (icon) {
		SDL_SetWindowIcon(_window, icon);
		SDL_FreeSurface(icon);
	}
	//SDL_RenderSetLogicalSize(_renderer, 0, 0);
	//DataManager::Get()->InitDataManager(this);
}

Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

void Window::Event()
{
	SDL_Event events;
	SDL_bool run = SDL_TRUE;
	
	while (SDL_PollEvent(&events)) {

		switch (events.type) 
	    {
		case SDL_WINDOWEVENT:
			if (events.window.event == SDL_WINDOWEVENT_CLOSE)
			{

				SDL_DestroyWindow(_window);
				
				std::cout << "WINDOW CLOSED";
				exit(0);
			}
				
		}
	}
}

bool Window::IsOpen()
{
	if (!_window)
	{
		return false;
	}
	return true;
}

void Window::Clear()
{
	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderClear(_renderer);
}

SDL_Renderer* Window::GetRenderer()
{
	return _renderer;
}

void Window::ShowDrawable(Drawable* drawable, Camera* _camera)

{
	if(drawable->GetAnimationState() == false)
		drawable->Draw(*this, _camera);
	else
	{
		drawable->DrawAnimatedEntity(*this, _camera);
	}
}

void Window::SetIsrunning(int state)
{
	if (state == 0)
		_isRunning = true;
	if(state == 1)
		_isRunning = false;
}

void Window::ShowCollider(RectCollider* rect, Camera* _camera)
{
	rect->Draw(*this, _camera);
}

void Window::ShowCollider(CircleCollider* circle, Camera* _camera)
{
	circle->Draw(*this, _camera);
}

float Window::GetWidth()
{
	return  SDL_GetWindowSurface(_window)->w;
}

float Window::GetHeight()
{
	return  SDL_GetWindowSurface(_window)->h;
}
void Window::Update()
{
	
	SDL_RenderPresent(_renderer);
}

void Window::End()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
	SDL_Quit();

}
