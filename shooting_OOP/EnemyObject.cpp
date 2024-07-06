#include "EnemyObject.h"
#include "BulletObject.h"

#include "SceneManager.h"
#include "FrameCounter.h"

#include "GameScene.h"




EnemyObject::EnemyObject(int x, int y, const EnemyType& type)
	: BaseObject{ x, y , Type::Enemy} , _type { type }
{
	
}

void EnemyObject::update()
{
	enemyMove();
	createBullet();
}
void EnemyObject::render(char buffer[SCREEN_HEIGHT][SCREEN_WIDTH])
{
	buffer[_ypos][_xpos] = _type.shape;
}

void EnemyObject::enemyMove()
{
	int moveX, moveY;
	int curX, curY, moveIndex;

	Movement& mv = _type._mv;
	moveIndex = mv.moveIndex % mv.moveCount;

	moveX = mv.moveData[moveIndex][0];
	moveY = mv.moveData[moveIndex][1];

	curX = _xpos;
	curY = _ypos;

	if ((curX + moveX > -1 && curX + moveX < SCREEN_WIDTH - 1) &&
		(curY + moveY > -1 && curY + moveY < SCREEN_HEIGHT))
	{
		if (mv.xHalf && curX + moveX > (SCREEN_WIDTH - 1) / 2)
		{
			mv.moveData[moveIndex][0] = -moveX;
			_xpos = curX - moveX;
		}
		else
			_xpos = curX + moveX;

		if (mv.yHalf && curY + moveY > (SCREEN_HEIGHT) / 2)
		{

			mv.moveData[moveIndex][1] = -moveY;
			_ypos = curY - moveY;

		}
		else
			_ypos = curY + moveY;
	}
	else
	{
		if (moveX > 0 || moveX < 0)
			mv.moveData[moveIndex][0] = -moveX;

		if (!mv.yOver && (moveY > 0 || moveY < 0))
			mv.moveData[moveIndex][1] = -moveY;

		_xpos = curX + -moveX;

		if (mv.yOver)
		{
			if (curY + moveY < 0)
				_ypos = SCREEN_HEIGHT - 1;
			else
				_ypos = 0;
		}
		else
			_ypos = curY + -moveY;
	}

	if (++(mv.moveIndex) == mv.moveCount)
		mv.moveIndex = 0;

}
void EnemyObject::createBullet()
{
	if (g_Frame == 0)
		_type.timer++;

	if (_type.timer >= _type.cooldown)
	{
		_type.timer = 0;
		for (int j{ _type.perAttackCount }; j > 0; --j)
			GameScene::_objList.push_back(new BulletObject(_xpos, _ypos + j, _type.attackShape, false, false));
	}
}
void EnemyObject::onCollision(BaseObject* obj)
{
	if (_isDelete || obj->isDelete())
		return;

	if (obj->getType() == BaseObject::Enemy)
		return;

	if (obj->getType() == BaseObject::Bullet)
	{
		if (static_cast<BulletObject*>(obj)->isPlayerBullet())
		{
			int targetX = obj->getX();
			int targetY = obj->getY();
			if (_xpos == targetX)
			{
				if (_ypos == targetY     ||
					_ypos == targetY + 1 ||
					_ypos == targetY - 1)
				{
					removeObject();
				}
			}
		}
	}

}