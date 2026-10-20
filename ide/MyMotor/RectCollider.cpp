#include "RectCollider.h"
#include "CircleCollider.h"

RectCollider::RectCollider(Vector2 position, Vector2 scale, Vector2 origin) :
	Collider(position, scale, origin) {
}

bool RectCollider::IsColliding(Collider* other)
{
	if (_isEnable != true)
	{
		return false;
	}

	if (RectCollider* otherRect = dynamic_cast<RectCollider*> (other))
	{
		Vector2 selfOrigin = GetOrigin();
		SetOrigin(0.5f, 0.5f);
		Vector2 pos1 = GetPos();

		Vector2 otherOrigin = GetOrigin();
		other->SetOrigin(0.5f, 0.5f);
		Vector2 pos2 = other->GetPos();

		int width1 = GetScale().GetX();
		int width2 = other->GetScale().GetX();

		int height1 = GetScale().GetY();
		int height2 = other->GetScale().GetY();

		bool betweenX = pos1.GetX() + width1 / 2 >= pos2.GetX() - width2 / 2 && pos1.GetX() - width1 / 2 <= pos2.GetX() + width2 / 2;
		bool betweenY = pos1.GetY() + height1 / 2 >= pos2.GetY() - height2 / 2 && pos1.GetY() - height1 / 2 <= pos2.GetY() + height2 / 2;

		// if (selfOrigin != GetOrigin()) TODO Surcharge d'opérateurs
		SetOrigin(selfOrigin.GetX(), selfOrigin.GetY());
		other->SetOrigin(otherOrigin.GetX(), otherOrigin.GetY());

		if (betweenX && betweenY) {
			return true;
		}

		return false;
	}
	else if (CircleCollider* otherCircle = dynamic_cast<CircleCollider*> (other))
	{
		//TODO
		return false;
	}
}