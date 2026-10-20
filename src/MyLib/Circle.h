#pragma once

#include "Drawable.h"
#include "Entity.h"

class Camera;
class Circle : public Entity
{
private:
 
    float _centerX = 0;
    float _centerY = 0;
    float _radius = 0;
    float _precision = 0;

protected:
    Circle* _sprite = nullptr;
public:
    void OnInitialize() override;
    void OnUpdate(float deltatime) override;
    void OnEnd() override;
    Circle(Vector2 pos, Vector2 scale, Vector2 origin);
    void Draw(Window& window, Camera* camera = nullptr) override;

};

