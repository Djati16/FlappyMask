#pragma once
#include "MyLib/Drawable.h";
#include <vector>
#include "RectCollider.h"
#include "MyLib/Collideable.h"
class Entity;
class Camera;
class Scene : public Drawable
{
private:
	const char* _name;
	std::vector<Entity*> _entities;
	std::vector<Entity*> _pendingDelete;
public:
	~Scene();
	void FlushDeleted();
	void SetName(const char* name);
	const char* GetName();

	template <typename T, typename ...Args>
	T* CreateEntity(Args&&... args)
	{
		T* tEntity = new T(std::forward<Args>(args)...);
		_entities.push_back(tEntity);
		return tEntity;
	}

	template <typename T>
	T* GetEntity()
	{
		for (auto entity : _entities)
		{
			if (T* tEntity = dynamic_cast<T*> (entity))
			{
				return tEntity;
			}
		}
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetAllEntity()
	{
		std::vector<T*> tEntities;

		for (auto entity : _entities)
		{
			if (T* tEntity = dynamic_cast<T*> (entity))
			{
				tEntities.push_back(tEntity);
			}
		}

		return tEntities;
	}


	std::vector<RectCollider*> GetAllRectColliders()
	{
		std::vector<RectCollider*> colliders;
		for (auto entity : _entities)
		{
			if (Collideable* c = dynamic_cast<Collideable*>(entity))
			{
				if (RectCollider* rc = c->GetRectCollider())
				{
					colliders.push_back(rc);
				}
			}
		}
		return colliders;
	}

	std::vector<CircleCollider*> GetAllCircleColliders()
	{
		std::vector<CircleCollider*> colliders;
		for (auto entity : _entities)
		{
			if (Collideable* c = dynamic_cast<Collideable*>(entity))
			{
				if (CircleCollider* rc = c->GetCircleCollider())
				{
					colliders.push_back(rc);
				}
			}
		}
		return colliders;
	}

	void DestroyEntity(Entity* entity);
	void Initialize();

	void Update(float deltaTime);

	void Draw(Window& window, Camera* _camera = nullptr) override;
};
