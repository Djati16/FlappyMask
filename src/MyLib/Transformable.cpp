#include "Transformable.h"

Transformable::Transformable(Vector2 pos, Vector2 scale, Vector2 origin)
{
	_pos = pos;
	_scale = scale;
	_origin = origin;
}

void Transformable::SetPos(float x, float y)
{
	_pos.InitX(x - (_scale.GetX() * _origin.GetX()));
	_pos.InitY(y - (_scale.GetY() * _origin.GetY()));
}

void Transformable::SetPosX(float x)
{
	_pos.InitX(x - (_scale.GetX() * _origin.GetX()));
}

void Transformable::SetPosY(float y)
{
	_pos.InitY(y - (_scale.GetY() * _origin.GetY()));
}

void Transformable::SetScale(float width, float height)
{
	_scale = { width, height };
}

void Transformable::SetOrigin(float anchorX, float anchorY)
{
	_origin = { anchorX, anchorY };
}

void Transformable::SetAtAnchor(Transformable* transformable, float anchorX, float anchorY)
{
	_pos.InitX(transformable->GetPos().GetX() - (transformable->GetScale().GetX() * anchorX));
	_pos.InitY(transformable->GetPos().GetY() - (transformable->GetScale().GetY() * anchorY));
}

/*void Transformable::SetAtAnchor(Transformable* transformable, float anchorX, float anchorY)
{
	// Calcule la position du point demandé sur le carré 2
	Vector2 pos = transformable->GetPos();
	Vector2 scale = transformable->GetScale();
	Vector2 origin = transformable->GetOrigin();

	// Décale du centre (anchor du carré 2) vers le point anchorX, anchorY
	float newX = pos.GetX() + (scale.GetX() * (anchorX - origin.GetX()));
	float newY = pos.GetY() + (scale.GetY() * (anchorY - origin.GetY()));

	SetPos(newX, newY);
}
*/

Vector2 Transformable::GetPos()
{
	Vector2 pos(_pos.GetX() + _scale.GetX() * _origin.GetX(), _pos.GetY() + _scale.GetY() * _origin.GetY());
	return pos;
}
Vector2 Transformable::GetRawPos()
{
	return _pos;
}
Vector2 Transformable::GetOrigin()
{
	return _origin;
}

Vector2 Transformable::GetScale()
{
	return _scale;
}



