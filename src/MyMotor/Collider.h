#pragma once
#include "MyLib/Entity.h"
class RectCollider;
class CircleCollider;

class Collider 
{
private:
    RectCollider* _rectangleCollider = nullptr;
    CircleCollider* _circleCollider = nullptr;
  
protected:
    Entity* _owner = nullptr;
    bool _isEnable = true;
    bool _collidingTopBot = false;
    bool _collidingLeftRight = false;
    float _overlapX = 0;
    float _overlapY = 0;

public:

   
   
    void EnableCollision();
    void DisableCollision();
    
	virtual bool IsColliding(Collider* other) = 0;
    friend class Point;
    friend class Player;
};

