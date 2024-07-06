#pragma once
#include "ScreenBuffer.h"
class BaseObject
{
public:

	enum Type
	{
		Player,
		Enemy,
		Bullet
	};

	BaseObject(int x, int y, Type objType);
	bool isDelete() const { return _isDelete; }
	void removeObject() { _isDelete = true; }
	Type getType() const { return _objType; }
	int getX() const { return _xpos; }
	int getY() const { return _ypos; }
	
public:
	virtual void update() = 0;
	virtual void render(char buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) = 0;
	virtual void onCollision(BaseObject* obj) {}
protected:
	bool _isDelete{ false };
	int _xpos;
	int _ypos;
	Type _objType;
};