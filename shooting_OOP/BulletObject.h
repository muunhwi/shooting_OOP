#pragma once
#include "BaseObject.h"
class BulletObject : public BaseObject
{
public:
	BulletObject(int x, int y, char attackShape, bool isPlayerBullet, bool reverse );
	void update() override;
	void render(char buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) override;
	


	bool isPlayerBullet() const { return _isPlayerBullet; }
	bool isReverse() const { return _reverse;  }
private:
	char _attackShape;
	bool _isPlayerBullet;
	bool _reverse;
};