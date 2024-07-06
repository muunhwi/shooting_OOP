#pragma once
#include "BaseObject.h"
class PlayerObject : public BaseObject
{
public:
	PlayerObject(char shape = 'P', char attackShape = '.');
	void update() override;
	void render(char buffer[SCREEN_HEIGHT][SCREEN_WIDTH]) override;
	void onCollision(BaseObject* obj) override;

private:
	void playerMove();
	void createBullet();

private:
	char _shape;
	char _attackShape;
	bool _attackKeyPressed{ false };
};