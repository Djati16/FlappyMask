#include "RectCollider.h"
#include "CircleCollider.h"
#include <iostream>
#include "Vector2.h"
#include "Window.h"							
#include "MyLib\Rectangle.h"

 
char mode = ' ';
RectCollider::RectCollider(Vector2 pos, Vector2 scale, Vector2 origin) : Rectangle(pos, scale, origin)
{
	_rect = { _pos.GetX(), _pos.GetY(), _scale.GetX(), _scale.GetY() };
	_sprite = new Rectangle(_pos, _scale, _origin);
	_show = true;
}

void RectCollider::Draw(Window& window, Camera* _camera)
{
	
	if (_show)
		_sprite->Draw(window, _camera);
}

bool RectCollider::IsColliding(RectCollider* other)
{
	if (_isEnable)
	{
		if (other != this)
		{
		
			Vector2 selfOrigin = GetOrigin();
			Vector2 pos1 = GetPos();

			
			Vector2 otherOrigin = other->GetOrigin();
			other->SetOrigin(0.5f, 0.5f);
			Vector2 otherPos = other->GetPos();

			float width = GetScale().GetX();
			float otherWidth = other->GetScale().GetX();

			float height = GetScale().GetY();
			float otherHeight = other->GetScale().GetY();

			bool betweenX = pos1.GetX() + width / 2 >= otherPos.GetX() - otherWidth / 2 && pos1.GetX() - width / 2 <= otherPos.GetX() + otherWidth / 2;
			bool betweenY = pos1.GetY() + height / 2 >= otherPos.GetY() - otherHeight / 2 && pos1.GetY() - height / 2 <= otherPos.GetY() + otherHeight / 2;

			float distX = other->GetPos().GetX() - this->GetPos().GetX();
			float distY = other->GetPos().GetY() - this->GetPos().GetY();

			SetOrigin(selfOrigin.GetX(), selfOrigin.GetY());
			other->SetOrigin(otherOrigin.GetX(), otherOrigin.GetY());

			if (betweenX && betweenY)
			{

				float overlapX = (width / 2 + otherWidth / 2) - abs(distX);
				float overlapY = (height / 2 + otherHeight / 2) - abs(distY);

				if (overlapX < overlapY)
				{
					_collidingLeftRight = true;
				}

				else
				{
					_collidingTopBot = true;

				}

				return true;

			}
			_collidingLeftRight = false;
			_collidingTopBot = false;
			return false;
		}
		_collidingLeftRight = false;
		_collidingTopBot = false;
		return false;
	}

}

void RectCollider::Repulse(RectCollider* other)
{
	if (_isEnable != true)
	{
		return;
	}
	Vector2 selfOrigin = GetOwner()->GetOrigin();
	if (mode != 's')
	{
		if(other != this)

	
		GetOwner()->SetOrigin(0.5f, 0.5f);
		Vector2 pos1 = GetOwner()->GetPos();


		Vector2 otherOrigin = other->GetOwner()->GetOrigin();
		other->GetOwner()->SetOrigin(0.5f, 0.5f);
		Vector2 otherPos = other->GetOwner()->GetPos();

		float width = GetScale().GetX();
		float otherWidth = other->GetOwner()->GetScale().GetX();

		float height = GetOwner()->GetScale().GetY();
		float otherHeight = other->GetOwner()->GetScale().GetY();

		float distX = other->GetOwner()->GetPos().GetX() - this->GetOwner()->GetPos().GetX();
		float distY = other->GetOwner()->GetPos().GetY() - this->GetOwner()->GetPos().GetY();

		Vector2 distVector{ distX, distY };

		float overlapX = (width / 2 + otherWidth / 2) - abs(distX);
		float overlapY = (height / 2 + otherHeight / 2) - abs(distY);

		if (overlapX < overlapY)
		{
			if (distX > 0)
			{
			
				GetOwner()->SetPos(GetOwner()->GetPos().GetX() - overlapX / 2, GetOwner()->GetPos().GetY());
				other->GetOwner()->SetPos(other->GetOwner()->GetPos().GetX(), other->GetOwner()->GetPos().GetY());


				SetPos(GetPos().GetX() - overlapX / 2,GetPos().GetY());
				other->SetPos(other->GetPos().GetX(), other->GetPos().GetY());
				_overlapX = -overlapX / 2;

			}

			else if (distX < 0)
			{
			

				GetOwner()->SetPos(GetOwner()->GetPos().GetX() + overlapX / 2, GetOwner()->GetPos().GetY());
				other->GetOwner()->SetPos(other->GetOwner()->GetPos().GetX(), other->GetOwner()->GetPos().GetY());



				SetPos(GetPos().GetX() + overlapX / 2, GetPos().GetY());
				other->SetPos(other->GetPos().GetX(), other->GetPos().GetY());
				_overlapX = overlapX / 2;

			}
			else
			{
				

				GetOwner()->SetPos(GetOwner()->GetPos().GetX() + overlapX / 2, GetOwner()->GetPos().GetY());
				other->GetOwner()->SetPos(other->GetPos().GetX() - overlapX / 2, other->GetPos().GetY());

				SetPos(GetPos().GetX() + overlapX / 2, GetPos().GetY());
				other->SetPos(other->GetPos().GetX() - overlapX / 2, other->GetPos().GetY());
				_overlapX = overlapX / 2;
			}

		}

		else
		{
			if (distY > 0)
			{
				GetOwner()->SetPos(GetOwner()->GetPos().GetX(), GetOwner()->GetPos().GetY() - overlapY);
				SetPos(GetPos().GetX(), GetPos().GetY() - overlapY);
				_overlapY = -overlapY;	
				_velocityY = 0;

			}

			else if (distY < 0)
			{

				GetOwner()->SetPos(GetOwner()->GetPos().GetX(), GetOwner()->GetPos().GetY() + overlapY);
				SetPos(GetOwner()->GetPos().GetX(), GetOwner()->GetPos().GetY() + overlapY);
				_overlapY = overlapY;
				_velocityY = 0;

			}

		}
		GetOwner()->SetOrigin(selfOrigin.GetX(), selfOrigin.GetY());
		other->GetOwner()->SetOrigin(otherOrigin.GetX(), otherOrigin.GetY());
	
	}
}


void RectCollider::RepulseRect(RectCollider* other)
{
	float dx = GetPos().GetX() - other->GetPos().GetX();
	float dy = GetPos().GetY() - other->GetPos().GetY();

	if (abs(dx) > abs(dy))
	{
		_direction.InitX(-_direction.GetX());
	}
	else
	{
		_direction.InitY(-_direction.GetY());
	}
}


void RectCollider::EnableCollision()
{
	_isEnable = true;
}

void RectCollider::DisableCollision()
{
	_isEnable = false;
}

