#pragma once
#include "MyLib/Drawable.h"
#include "MyLib/Rectangle.h"
#include "SDL.h"

class Collideable;
class RectCollider : public Rectangle
{
private:

    Entity* _owner;
    Vector2 pos1;
    Vector2 _previousPos;
    bool _isEnable = true;
   
    float _overlapX = 0;
    float _overlapY = 0;

protected:
    Rectangle* _sprite;
   
public:
    RectCollider(Vector2 pos, Vector2 scale, Vector2 origin);
    bool _collidingTopBot = false;
    bool _collidingLeftRight = false;
    

    void EnableCollision();
    void DisableCollision();
    void RepulseRect(RectCollider* other);
    void Draw(Window& window, Camera* _camera = nullptr) override;
    bool IsColliding(RectCollider* other);
    void Repulse(RectCollider* other);
    void SetOwner(Entity* owner) { _owner = owner; }
    Entity* GetOwner() { return _owner; }

    friend class Player;
    friend class Point;
};

