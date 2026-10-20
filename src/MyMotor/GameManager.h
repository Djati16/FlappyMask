#pragma once
#include <string>
std::string ComputeChecksum(int score);
int LoadVerifiedHighScore();
#include "SceneManager.h"
#include <iostream>

class Window;
class Camera;
class LevelManager;
class Timer;
class ClickerManager;
class Input;
class Writer;
class Sprite;
class Player;
class UI;
class BackGround;
class BackGroundManager;
class SoundLector;

class GameManager
{
private:
	
	
	UI* _ui = nullptr;

	Input* _input = nullptr;
	Window* _window = nullptr;
	Player* _player = nullptr;
	Camera* _camera = nullptr;
	Scene* _playerScene = nullptr;
	ClickerManager* _clickerManager = nullptr;
	BackGroundManager* _backGroundManager = nullptr;

	std::vector<Entity*> _entities;
	std::vector<Rectangle*> _rectangles;
	std::vector<Collideable*> _collideables;
	std::vector<Point*> _checkPoints;
	std::vector<RectCollider*> _rectColliders;
	std::vector<CircleCollider*> _circleColliders;
	std::unique_ptr<Timer> _timer = nullptr;
	std::unique_ptr<Writer> _writer = nullptr;
	std::unique_ptr<LevelManager> _levelManager = nullptr;

	float count = 0.f;
	int _frameCount = 0;
	int _lastScore = 0;
	bool _musicMutted = false;
	bool  _quitRequested = false;
	float _camRight = 0.f;
	float _camLeft = 0.f;
	float _camTop = 0.f;
	float _camBot = 0.f;
	float _avgFps = 0.f;
	float _offsetX = 0.f;
	float _deltatime = 0.f;
	float _miniTimer = 0.f;
	float _accumulator = 0.f;
	float fixedStep = 1.f / 60.f;
	bool _gameOver = false;
	bool _gameOverSet = false;
	bool _waitingScreen = false;
	float _waitingScrollX = 0; 
	float _waitingScrollSpeed = 100;
public:

	GameManager(const char* title = "Game", int x = 500, int y = 250, int w = 500, int h = 500, unsigned int flags = 0);
	~GameManager();
	SceneManager* GetSceneManager();
	void SetPlayerScore(int score);
	int GetPlayerScore();

	void Initialize();
	void InitializeOnce();
	void ResetGame();
	void Loop();

	void Restart();
	int LoadHighScore();
	int LoadLastScore();
	bool LoadMusicVolumeState(bool state);
	Window& GetWindow();
	Player* Get_Player();
	float GetOffsetX();
	GameManager* GetSelf() { return this; }
	UI* GetUI();

};