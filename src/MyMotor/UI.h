#pragma once
#include "MyLib/Entity.h"
#include "MyLib/Rectangle.h"
#include "MyLib/Writer.h"
#include <vector>

class Window;
class Input;

class UI : public Rectangle , public Writer
{
private:
	Input* _input = nullptr;
	std::vector<Rectangle*> _uiRectangle;
	Rectangle* _menu = nullptr;
	Rectangle* _quitButton = nullptr;
	Rectangle* _replayButton = nullptr;
	Rectangle* _muteButton = nullptr;
	Rectangle* _title = nullptr;
	Window* _window = nullptr;
	int _playerScore = 0;
	int _playerLastScore = 0;
	int _playerHighScore = 0;
	bool _isGameOver = false;
	bool _mouseOnQuitButton = false;
	bool _mouseOnReplayButton = false;
	bool _mouseOnMuteButton = false;
	bool _titleDrew = false;
	bool _muted = false;
	float _titleDirection = -2;
	float _titleHeight = -0.5;
	int _replayCount = 0;
	float _maxX = 0;
	float _minX = 0;
	float _maxY = 0;
	float _minY = 0;
public:
	UI(Window& window, Vector2 pos, Vector2 scale, Vector2 origin = { 0, 0 }, int tag = -1);
	void Draw(Window& window, Camera* _camera = nullptr) override;
	void DrawMenu(Window& window, Camera* _camera);
	
	void OnInitialize() override;
	void OnUpdate(float deltatime) override;
	void CheckMousePos(float mouseX, float mouseY, float buttonX, float buttonY, float buttonScaleX, float buttonScaleY, bool &boolean);
	void OnEnd() override;

	void SetSprite(Window& window, std::initializer_list<const char*> assets);
	void SetGameOver(const char* text);

	void SetPlayerScore(int score);
	void SetPlayerLastScore(int lastScore);
	void SetPlayerHighScore(int highScore);
	void SetMusicIsmuted(bool state);
	void SetMusicState(bool state);
	int GetPlayerScore();
	int GetPlayerLastScore();
	int GetPlayerHighScore();
	Rectangle* GetTitle();

	bool MouseOnQuitButton();
	//bool MouseOnMuteButton();
	bool MouseOnReplayButton();
	bool GetMuteState();

	void AddReplayCount();

	int GetReplayCount() { return _replayCount; }
	bool TitleIsdraw() { return _titleDrew; }
	void ShowText(const char* text,bool useAnchor, float X, float Y, float anchorX = 0, float anchorY = 0, int size = 0, Rectangle* r = nullptr);
	void ShowNumber(int number, bool useAnchor, float X, float Y, float anchorX = 0, float anchorY = 0, Rectangle* r = nullptr);
	void CreateQuitButton(Window& window, float anchorX, float anchorY, float width, float height, Rectangle* r = nullptr);
	void CreateReplaytButton(Window& window, float anchorX, float anchorY, float width, float height, Rectangle* r = nullptr);
	void CreateMuteButton(Window& window, float x, float y, float width, float height);
	void SwitchIcon(Window& window);
	void CreateTitle(Window& window, float x, float y, float width, float height);
	void DrawButtons(Window& window, Camera* _camera);
	void DrawTitle(Window& window, Camera* _camera);
	void DrawMuteButton(Window& window, Camera* _camera);
	void MooveTile(int state);
	void MoveUpdate(float x, float y);
};

