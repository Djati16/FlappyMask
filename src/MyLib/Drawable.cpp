#include "Drawable.h"
#include <iostream>



void Drawable::SetAnimationState(const char* a)
{
	if (a == "true")
		_animated = true;
	else if (a == "false")
		_animated = false;
}

bool Drawable::GetAnimationState()
{
	return _animated;
}
void Drawable::SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{ 
	_color._r = r;
	_color._g = g;
	_color._b = b;
	_color._a = a;
}

void Drawable::DrawAnimatedEntity(Window& window, Camera* _camera)
{
}

unsigned char Drawable::GetR()
{
	return _color._r;
}
unsigned char Drawable::GetG()
{
	return  _color._g;
}
unsigned char Drawable::GetB()
{
	return  _color._b;
}
unsigned char Drawable::GetA()
{
	return  _color._a;
}
