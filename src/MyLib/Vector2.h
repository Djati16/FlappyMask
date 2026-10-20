#pragma once

class Vector2
{
protected:
	float _x = 0.f;
	float _y = 0.f;

public:
	Vector2(float x = 0, float y = 0);

	float GetDistance(Vector2 otherVect);

	void InitX(float x);
	void InitY(float y);

	float GetX();
	float GetY();
	friend  class Entity;
	friend class Player;
	friend class UI;
	
};

