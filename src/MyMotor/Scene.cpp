#include "Scene.h"
#include "Entity.h"
#include "MyMotor/Camera.h"
#include <iostream>
#include "MyMotor/RectCollider.h"
Scene::~Scene()
{
	for (auto& entity : _entities)
	{
		delete entity;
	}
}

void Scene::SetName(const char* name)
{
	_name = name;
}

const char* Scene::GetName()
{
	return _name;
}

void Scene::Initialize()
{
	for (auto entity : _entities)
	{
		entity->OnInitialize();
	}
}
void Scene::Update(float deltaTime)
{
	for (auto entity : _entities)
	{
 		entity->OnUpdate(deltaTime);
	}
}

void Scene::Draw(Window& window, Camera* _camera)
{
	for (auto entity : _entities)
	{
		entity->Draw(window, _camera);

	}
	
}

void Scene::DestroyEntity(Entity* entity)
{
	_entities.erase(
		std::remove(_entities.begin(), _entities.end(), entity),
		_entities.end()
	);
	//std::cout << "Entite detruite";
	_pendingDelete.push_back(entity);
}

void Scene::FlushDeleted()
{
	for (Entity* e : _pendingDelete)
		delete e;
	_pendingDelete.clear();
}