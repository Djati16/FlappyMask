#pragma once
class PlayerScene;
class SceneManager;
class Player;
class Camera;
class LevelManager
{
protected:
	int _i = 0;
	float _pipeDistance = 0;
	float _groundDistance = 0;
	bool _groundCanBeCreated = false;
	float _initialX;
	int _groundCount = 0;
	bool _levelHasBegin = false;
	Camera* _camera = nullptr;
public:
	LevelManager();
	void SetCamera(Camera* _camera);
	Camera* GetCamera() { return _camera; };
	void OnInitialize() ;
	void OnUpdate(float deltatime, Player* player) ;
	void OnEnd();
	
	void RandomPatern(int count);
	void ObstacleManager(char d, int count);
	
};

