#include "UI.h"
#include "MyLib/Writer.h"
#include "MyLib/Window.h"
#include <string>
#include "MyLib/Input.h"
#include <iostream>
#include "MyLib/SoundLector.h"

UI::UI(Window& window, Vector2 pos, Vector2 scale, Vector2 origin, int tag) : Rectangle(pos, scale, origin, tag) , Writer()
{
	_window = &window;
	_menu = new Rectangle(_pos, _scale, _origin);
	_input = _input->Get();
	_menu->SetSprite(window, "uiFont.bmp");
	_menu->SetCamAffected("false");
	
}

void UI::ShowText(const char* text, bool useAnchor, float X, float Y, float anchorX, float anchorY, int size, Rectangle* r)
{
	InitColor(255, 255, 255);

	if (useAnchor == false)
		Write(text, *_window, X, Y);
	else
	{
		if(r == nullptr)
			r = _menu;
		Vector2 pos = r->GetPos();
		Vector2 scale = r->GetScale();
		Vector2 origin = r->GetOrigin();

		float x = pos.GetX() + (scale.GetX() * (anchorX - origin.GetX()));
		float y = pos.GetY() + (scale.GetY() * (anchorY - origin.GetY()));

		Write(text, *_window, x, y);
	}
}

void UI::ShowNumber(int number, bool useAnchor, float X, float Y, float anchorX, float anchorY, Rectangle* r)
{
	if(useAnchor == false)
		Write(std::to_string(number).c_str(), *_window, X, Y);
	else	
	{
		if (r == nullptr)
			r = _menu;
		Vector2 pos = r->GetPos();
		Vector2 scale = r->GetScale();
		Vector2 origin = r->GetOrigin();

		float x = pos.GetX() + (scale.GetX() * (anchorX - origin.GetX()));
		float y = pos.GetY() + (scale.GetY() * (anchorY - origin.GetY()));

		Write(std::to_string(number).c_str(), *_window, x, y);
	}
}

void UI::Draw(Window& window, Camera* _camera)
{
	DrawMenu(window, _camera);
	DrawButtons(window, _camera);
}

void UI::DrawMenu(Window& window, Camera* _camera)
{
	_menu->DrawSprite(window, _camera);
	
}

void UI::CreateQuitButton(Window& window, float anchorX, float anchorY, float width, float height, Rectangle* r)
{
	if (r == nullptr)
		r = _menu;
	Vector2 pos = r->GetPos();
	Vector2 scale = r->GetScale();
	Vector2 origin = r->GetOrigin();

	float x = pos.GetX() + (scale.GetX() * (anchorX - origin.GetX()));
	float y = pos.GetY() + (scale.GetY() * (anchorY - origin.GetY()));

	_quitButton = new Rectangle(Vector2(x, y), Vector2(width, height), Vector2(0, 0));
	_quitButton->SetSprite(window, "quitTest3.bmp");
	_quitButton->SetCamAffected("false");
	_quitButton->SetColor(0, 255, 255);
	std::cout << "Quit cree";
}

void UI::CreateReplaytButton(Window& window, float anchorX, float anchorY, float width, float height, Rectangle* r)
{
	if (r == nullptr)
		r = _menu;
	Vector2 pos = r->GetPos();
	Vector2 scale = r->GetScale();
	Vector2 origin = r->GetOrigin();

	float x = pos.GetX() + (scale.GetX() * (anchorX - origin.GetX()));
	float y = pos.GetY() + (scale.GetY() * (anchorY - origin.GetY()));
	
	_replayButton = new Rectangle(Vector2(x, y), Vector2(width, height), Vector2(0, 0));
	_replayButton->SetSprite(window, "ReplayBtn.bmp");
	_replayButton->SetCamAffected("false");
	_replayButton->SetColor(255, 255, 255);
	std::cout << "Replay cree";
}

void UI::CreateMuteButton(Window& window, float x, float y, float width, float height) 
{

	_muteButton = new Rectangle(Vector2(x, y), Vector2(width, height), Vector2(0, 0));

	_muteButton->SetCamAffected("false");
	_muteButton->SetColor(255, 255, 255);

}
void UI::SwitchIcon(Window& window)
{

	if (_muted == false)
		_muteButton->SetSprite(window, "unmute.bmp");
	else
		_muteButton->SetSprite(window, "mute.bmp");
}

void UI::CreateTitle(Window& window, float x, float y, float width, float height)
{

	_title = new Rectangle(Vector2(x, y), Vector2(width, height), Vector2(0, 0));
	_title->SetSprite(window, "flappyMaskTitle.bmp");
	_title->SetCamAffected("false");
	_title->SetColor(255, 255, 255);
	_maxX = _title->GetPos().GetX() + 50;
	_minX = _title->GetPos().GetX() - 50;
	_maxY = _title->GetPos().GetY() + 20;
	_minY = _title->GetPos().GetY() - 20;
	std::cout << "Title cree";
}

void UI::DrawButtons(Window& window, Camera* _camera)
{
	
	_quitButton->DrawSprite(window, _camera);
	
	_replayButton->DrawSprite(window, _camera);


}

void UI::DrawTitle(Window& window, Camera* _camera)
{
	_title->DrawSprite(window, _camera);
	_titleDrew = true;
}

void UI::DrawMuteButton(Window& window, Camera* _camera)
{
	_muteButton->DrawSprite(window, _camera);

}

void UI::MoveUpdate(float x, float y)
{
	float newPosX = _title->GetPos().GetX() + x;
	float newPosY = _title->GetPos().GetY() + y;

	_title->SetPos(newPosX, newPosY);

}

void UI::MooveTile(int state)
{
	float actualX = _title->GetPos().GetX();
	float actualY = _title->GetPos().GetY();
	if (state == 0)
	{
		if (actualY <= _minY)
			_titleHeight = 0.5;
		else if (actualY >= _maxY)
			_titleHeight = -0.5;
		MoveUpdate(0, _titleHeight);
	}
	else
	{
		MoveUpdate(0, -3);
	}
}

Rectangle* UI::GetTitle()
{
	return _title;
}

void UI::OnInitialize()
{
	Initialize();
}

void UI::OnUpdate(float deltatime)
{
	float mouseX = _input->GetMouseX();
	float mouseY = _input->GetMouseY();
	if(_muteButton != nullptr)
	{
		float muteButtonX = _muteButton->GetPos().GetX();
		float muteButtonY = _muteButton->GetPos().GetY();

		float muteButtonScaleX = _muteButton->GetScale().GetX();
		float muteButtonScaleY = _muteButton->GetScale().GetY();

		//CheckMousePos(mouseX, mouseY, muteButtonX, muteButtonY, muteButtonScaleX, muteButtonScaleY, _mouseOnMuteButton);
	}

	if(_isGameOver)
	{
		float quitButtonX = _quitButton->GetPos().GetX();
		float quitButtonY = _quitButton->GetPos().GetY();

		float replayButtonX = _replayButton->GetPos().GetX();
		float replayButtonY = _replayButton->GetPos().GetY();

		float replayButtonScaleX = _replayButton->GetScale().GetX();
		float replayButtonScaleY = _replayButton->GetScale().GetY();
		

		float quitButtonScaleX = _quitButton->GetScale().GetX();
		float quitButtonScaleY = _quitButton->GetScale().GetY();

		CheckMousePos(mouseX, mouseY, quitButtonX, quitButtonY, quitButtonScaleX, quitButtonScaleY, _mouseOnQuitButton);
		CheckMousePos(mouseX, mouseY, replayButtonX, replayButtonY, replayButtonScaleX, replayButtonScaleY, _mouseOnReplayButton);
	}
	_menu->SetPos(_pos.GetX(), _pos.GetY());
}

void UI::CheckMousePos(float mouseX, float mouseY, float buttonX, float buttonY, float buttonScaleX, float buttonScaleY, bool &boolean)
{
	if (mouseX >= buttonX && mouseX <= buttonX + buttonScaleX && mouseY >= buttonY && mouseY <= buttonY + buttonScaleY)
	{
		boolean = true;
	}

	else 
	{
		boolean = false;
	}
}

void UI::OnEnd()
{
	Clean();
}

void UI::SetGameOver(const char* text)
{
	if (text == "true")
		_isGameOver = true;
	else
		_isGameOver = false;
}

void UI::SetPlayerScore(int score)
{
	_playerScore = score;
}

void UI::SetPlayerLastScore(int lastScore)
{
	_playerLastScore = lastScore;
}

void UI::SetPlayerHighScore(int highScore)
{
	_playerHighScore = highScore;
}

void UI::SetMusicIsmuted(bool state)
{
	
	if (_muted)
	{
		_muted = false;
	
		std::cout << "unMuted";
		SoundLector::GetInstance()->SetMusicVolume(50);
	}
	else
	{
		_muted = true;
		std::cout << "Muted";
		SoundLector::GetInstance()->SetMusicVolume(0);
	}
}
void UI::SetMusicState(bool state)
{
	_muted = state;
}

bool UI::GetMuteState()
{
	return _muted;
}
int UI::GetPlayerScore()
{
	return _playerScore;
}
int UI::GetPlayerLastScore()
{
	return _playerLastScore;
}
int UI::GetPlayerHighScore()
{
	return _playerHighScore;
}

bool UI::MouseOnQuitButton()
{
	return _mouseOnQuitButton;
}


bool UI::MouseOnReplayButton()
{
	return _mouseOnReplayButton;
}
void UI::AddReplayCount()
{
	_replayCount += 1;
}