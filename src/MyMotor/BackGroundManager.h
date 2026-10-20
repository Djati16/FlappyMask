#pragma once
#include <vector>
#include "MyLib/Vector2.h"
class Sprite;
class Window;
class Camera;
class Vector2;
class BackGroundManager
{
private:
	
	int _backGroundCount = 0;
	std::vector<Sprite*> _backGrounds;

public:
	BackGroundManager();
	Sprite* GetBackGround(int i);
	void LoadBackGround(Window& window, const char* name);
	void DrawAllBackGrounds(Window& window, Camera* camera);
	void SetBackGroundScale(int i, float width, float height);
	void SetBackGroundPos(int i, float x, float y);

};

