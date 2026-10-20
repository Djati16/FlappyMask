#pragma once
#include "MyLib\Collideable.h"
#include "MyLib\Entity.h"
#include <initializer_list>

class Circle; 
class Sprite;
class Input;
class Window;
class GameManager;
class SoundLector;


class Player : public Collideable, public Entity
{
private:

	Sprite* _sprite = nullptr;
	Input* _input = nullptr;
	GameManager* _manager = nullptr;
	SoundLector* soundLector = nullptr;

	float _dashTimer = 0.f;
	float _dashDuration = 0.30f;
	float _dashSpeed = 50000.f;
	bool _isFlying = false;
	bool _waitingState = true;

	float _moveY = 0;
	float _moveX = 0;
	float _waitingHeight = -0.5;
	float _maxY = 0;
	float _minY = 0;
	float _gravity = 0;
	float _timer = 0;
	float _progression = 1;

	int _groundAccumulator = 0;
	int _doubleJumpCount = 0;


public:

	Player(Vector2 pos, Vector2 scale, Vector2 origin, int tag = -1);
	
	~Player();
	
	void OnInitialize() override;
	void OnCollision(Collideable* other) override;
	void OnUpdate(float deltatime) override;
	void Draw(Window& window, Camera* _camera = nullptr) override;

	void AddScore(int i);
	void AddProgression(int i);
	int _score = 0;
	Player* GetPlayer();
	void Fly();
	void UpdatePos();
	void OnEnd() override;
	void UpdateXPos(float x);
	void UpdateYPos(float y);
	void Move(float delatime);
	void MoveUpdate(float x, float y);
	void MooveInWaitingState();

	int SaveHighScore(int score);
	int GetProgression() { return _progression; };
	int GetScore() { return _score; };
	void SetSprite(Window& window, const char* asset) override;
	void SetSprite(Window& window, std::initializer_list<const char*> assets);
	void SetWaitingState(int state);
	bool GetWaitingState() { return _waitingState; }
	friend Camera;
	friend class LevelManager;
	friend class Point;
	friend  GameManager;
};

