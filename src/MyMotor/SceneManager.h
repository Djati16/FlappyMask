#pragma once
#include <map>
#include "Scene.h"

class SceneManager
{
private:
	std::map<const char*, Scene*> _scenes = {};
	Scene* _currentScene = nullptr;
	static SceneManager* _instance;
public:
	
	static SceneManager* GetInstance()
	{
		if (_instance == nullptr)
			_instance = new SceneManager();
		return _instance;
	}
	~SceneManager();

	void AddScene(const char* name, Scene* scene);
	void RemoveScene(const char* name);

	Scene* GetScene(const char* name);
	Scene* GetCurrentScene();
	SceneManager* GetSelf();
	void SetCurrentScene(const char* name);
	friend class Camera;
	friend class LevelManager;
	friend class GameManager;
};
