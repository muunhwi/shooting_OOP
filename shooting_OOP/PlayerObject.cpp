#include "PlayerObject.h"
#include "BulletObject.h"

#include "GameScene.h"

PlayerObject::PlayerObject(char shape, char attackShape)
	: BaseObject{ (SCREEN_WIDTH - 1) / 2, SCREEN_HEIGHT - 1, Type::Player}, _shape {shape}, _attackShape{ attackShape }
{

}
void PlayerObject::update()
{
	playerMove();
	createBullet();
}
void PlayerObject::render(char buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	buffer[_ypos][_xpos] = _shape;
}

void PlayerObject::onCollision(BaseObject* obj)
{
	int targetX = obj->getX();
	int targetY = obj->getY();
	if (_xpos == targetX)
	{
		if (_ypos == targetY ||
			_ypos == targetY + 1 ||
			_ypos == targetY - 1)
		{
			removeObject();
		}
	}

}


void PlayerObject::playerMove()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (_xpos > 0)
			_xpos--;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (_xpos < SCREEN_WIDTH - 2)
			_xpos++;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		if (_ypos > 0)
			_ypos--;
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		if (_ypos < SCREEN_HEIGHT - 1)
			_ypos++;
	}
}
void PlayerObject::createBullet()
{
	if (!_attackKeyPressed)
	{
		if (GetAsyncKeyState(0x5A)) // z
		{
			if (_ypos > 0)
				GameScene::_objList.push_back(new BulletObject(_xpos, _ypos - 1, _attackShape, true, false));
		}
		else if (GetAsyncKeyState(0x58)) // x
		{
			if (_ypos < SCREEN_HEIGHT - 1)
				GameScene::_objList.push_back(new BulletObject(_xpos, _ypos + 1, _attackShape, true, true));
		}
		_attackKeyPressed = true;
	}
	else
		_attackKeyPressed = false;
}