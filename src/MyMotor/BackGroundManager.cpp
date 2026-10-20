#include "BackGroundManager.h"
#include "MyLib/Sprite.h"

BackGroundManager::BackGroundManager()
{
}

Sprite* BackGroundManager::GetBackGround(int i)
{
	return _backGrounds[i];
}

void BackGroundManager::LoadBackGround(Window& window, const char* name)
{
	
	Sprite* backGround = new Sprite(Vector2(0, 0), Vector2(0, 0), Vector2(0, 0));
	_backGrounds.push_back(backGround);
	backGround->SetCamAffected("false");
	backGround->LoadUniqueImage(window, name);

	_backGroundCount += 1;
	
}


void BackGroundManager::DrawAllBackGrounds(Window& window, Camera* camera)
{
	for (int i = 0; i < _backGrounds.size(); i++)
	{
		_backGrounds[i]->Draw(window, camera);
	}
}

void BackGroundManager::SetBackGroundScale(int i,  float width, float height)
{
	_backGrounds[i]->SetScale(width, height);
}

void BackGroundManager::SetBackGroundPos(int i, float x, float y)
{
	_backGrounds[i]->SetPos(x, y);
}
