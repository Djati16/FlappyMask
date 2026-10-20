#pragma once
class Window;
class Camera;

class Drawable
{
private:
	bool _animated = false;
	struct Color
	{
		unsigned char _r;
		unsigned char _g;
		unsigned char _b;
		unsigned char _a;
	};
protected:
	Color _color;

public:
	unsigned char GetR();
	unsigned char GetG();
	unsigned char GetB();
	unsigned char GetA();

	void SetAnimationState(const char* a);
	bool GetAnimationState();
	void SetColor(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255);
	virtual void Draw(Window& window, Camera* _camera = nullptr) = 0;
	virtual void DrawAnimatedEntity(Window& window, Camera* _camera = nullptr);

	virtual ~Drawable() = default;
};

