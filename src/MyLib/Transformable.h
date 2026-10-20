#pragma once

#include "Vector2.h"

class Transformable
{
protected:
	Vector2 _pos;
	Vector2 _origin;
	Vector2 _scale;

public:
	Transformable(Vector2 pos, Vector2 scale, Vector2 origin);
	virtual ~Transformable() = default;
	void SetPos(float x, float y);
	void SetPosX(float x);
	void SetPosY(float y);
	void SetScale(float width, float height);
	void SetOrigin(float anchorX, float anchorY);
	void SetAtAnchor(Transformable* transformable, float anchorX, float anchorY);
	Vector2 GetPos();
	Vector2 GetRawPos();
	Vector2 GetScale();
	Vector2 GetOrigin();

	friend class Entity;
	friend class Ground;
	friend class Player;
	friend class Proto;
	friend class StaticObject;
};

