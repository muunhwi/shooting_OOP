#include "BulletObject.h"

BulletObject::BulletObject(int x, int y, char attackShape,  bool isPlayerBullet, bool reverse)
	: BaseObject{x,y, Type::Bullet}, _attackShape { attackShape }, _isPlayerBullet { isPlayerBullet }, _reverse { reverse}
{}
void BulletObject::update()
{
	if (!_isPlayerBullet || (_isPlayerBullet && _reverse))
	{
		++_ypos;
		if (_ypos >= SCREEN_HEIGHT)
			removeObject();
	}
	else
	{
		--_ypos;
		if (_ypos < 0)
			removeObject();
	}
	
}
void BulletObject::render(char buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	buffer[_ypos][_xpos] = _attackShape;
}
