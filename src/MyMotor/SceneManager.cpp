#include "SceneManager.h"
#include <iostream>


SceneManager* SceneManager::_instance = nullptr;
SceneManager::~SceneManager()
{
	for (auto it = _scenes.begin(); it != _scenes.end(); ++it)
	{
		delete (*it).second;
	}
}

void SceneManager::AddScene(const char* name, Scene* scene)
{
	auto it = _scenes.find(name);

	if (it == _scenes.end())
		_scenes[name] = scene;
}

void SceneManager::RemoveScene(const char* name)
{
	auto it = _scenes.find(name);

	if (it == _scenes.end())
		return;

	delete it->second;
	_scenes.erase(it->first);
}

Scene* SceneManager::GetScene(const char* name)
{
	auto it = _scenes.find(name);

	if (it == _scenes.end())
		return nullptr;

	_scenes.contains(name);
	return _scenes[name];
}

Scene* SceneManager::GetCurrentScene()
{
	return _currentScene;
}

void SceneManager::SetCurrentScene(const char* name)
{
	auto it = _scenes.find(name);

	if (it == _scenes.end())
		return;

	_currentScene = it->second;
}

SceneManager* SceneManager::GetSelf()
{
	return this;
}