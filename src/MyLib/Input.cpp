#include "Input.h"
#include "SDL.h"
#include <iostream>

Input* Input::Instance = nullptr;

Input::Input()
{
	Instance = nullptr;
}

Input* Input::Get()
{
	if (Instance == nullptr)
	{
		Instance = new Input;
	}

	return Instance;
}

void Input::Update() {

	SDL_PumpEvents();
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	Uint32 boutons = SDL_GetMouseState(&mouseX, &mouseY);
	
	for (int i = 0; i < KEYCODE_KEYCODES; ++i)
	{
		_keys[i].isKeyDown = false;
		_keys[i].isKeyUp = false;

		if (_keys[i].lastState == Down)
		{
			_keys[i].isKeyHeld = keyboardState[i];

			if (_keys[i].isKeyHeld)
			{
				_keys[i].lastState = Held;
			}
		}
		if (_keys[i].lastState != Held)
		{
			_keys[i].isKeyDown = keyboardState[i];

			if (_keys[i].isKeyDown)
			{
				_keys[i].lastState = Down;
			}
		}
		if ((_keys[i].lastState == Down || _keys[i].lastState == Held) && keyboardState[i] == 0)
		{
			_keys[i].isKeyUp = true;

			_keys[i].isKeyHeld = false;

			_keys[i].lastState = Released;
		}
	}
	bool mouseState[3] = 
	{
		(boutons & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
		(boutons & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0,
		(boutons & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0
	};

	for (int i = 0; i < 3; ++i)
	{
		_mouseButtons[i].isKeyDown = false;
		_mouseButtons[i].isKeyUp = false;
		if (_mouseButtons[i].lastState == Down)
		{
			_mouseButtons[i].isKeyHeld = mouseState[i];
			if (_mouseButtons[i].isKeyHeld)
			{
				_mouseButtons[i].lastState = Held;
			}
		}
		if (_mouseButtons[i].lastState != Held)
		{
			_mouseButtons[i].isKeyDown = mouseState[i];
			if (_mouseButtons[i].isKeyDown)
			{
				_mouseButtons[i].lastState = Down;
			}
		}
		if ((_mouseButtons[i].lastState == Down || _mouseButtons[i].lastState == Held) && mouseState[i] == 0)
		{
			_mouseButtons[i].isKeyUp = true;
			_mouseButtons[i].isKeyHeld = false;
			_mouseButtons[i].lastState = Released;
		}
	}
}

bool Input::IsKeyDown(KeyCode keycode)
{
	return _keys[keycode].isKeyDown;
}

bool Input::IsKeyHeld(KeyCode keycode)
{
	return _keys[keycode].isKeyHeld;
}

bool Input::IsKeyUp(KeyCode keycode)
{
	return _keys[keycode].isKeyUp;
}

bool Input::IsMouseDown(int button) 
{
	return _mouseButtons[button].isKeyDown;
}

bool Input::IsMouseHeld(int button)
{ 
	return _mouseButtons[button].isKeyHeld; 
}

bool Input::IsMouseUp(int button)
{
	return _mouseButtons[button].isKeyUp;
}

int  Input::GetMouseX() 
{ 
	return mouseX;
}

int  Input::GetMouseY() 
{
	return mouseY;
}