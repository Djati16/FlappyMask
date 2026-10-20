#pragma once
#include "MyLib/Entity.h"
#include "RectCollider.h"
#include "CircleCollider.h"
#include "Timer.h"

class Vector2;

class CollidableEntity :public Entity
{
protected:

    RectCollider* _rectangleCollider = nullptr;
    CircleCollider* _circleCollider = nullptr;
    Timer* _miniTimer = nullptr;
   
 

public:
    CollidableEntity(Vector2 pos, Vector2 scale, Vector2 origin);

   

    friend class StaticObject;
   
};

