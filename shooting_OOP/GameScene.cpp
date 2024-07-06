#include "SceneManager.h"
#include "StageInfo.h"
#include "FrameCounter.h"

#include "GameScene.h"
#include "OverScene.h"
#include "WinScene.h"
#include "ClearScene.h"

#include "EnemyObject.h"
#include "PlayerObject.h"

MyLinkedList<BaseObject*> GameScene::_objList;

GameScene::GameScene()
{
	bufferClear();

	StageInfo* info = StageInfo::getInstance();
	const std::vector<EnemyType>& enemyTypes = info->getEnemyTypes();
	const std::vector<Stage>& stages = info->getStages();

	_objList.push_back(new PlayerObject);

	for (std::size_t i{ 0 }; i < stages.size(); ++i)
	{
		for (std::size_t j{ 0 }; j < enemyTypes.size(); ++j)
		{
			if (stages[i].shape == enemyTypes[j].shape)
				_objList.push_back(new EnemyObject(stages[i].x, stages[i].y, enemyTypes[j]));
		}
	}


}
GameScene::~GameScene()
{
	for (auto iter = _objList.begin(); iter != _objList.end(); iter = _objList.erase(iter))
		delete (*iter);
}
void GameScene::update()
{
	SceneManager* manager = SceneManager::getInstance();
	StageInfo* info = StageInfo::getInstance();

	BaseObject* curObj;
	BaseObject* targetObj;

	for (auto iter = _objList.begin(); iter != _objList.end(); ++iter)
		(*iter)->update();
		
	auto iter = _objList.begin();
	for (; iter != _objList.end(); ++iter)
	{
		//(*iter)->update();
		curObj = *iter;
	
		auto target = iter;
		for (++target; target != _objList.end(); ++target)
		{
			targetObj = *target;
			
			curObj->onCollision(targetObj);
			targetObj->onCollision(curObj);
		}
	}

	iter = _objList.begin();
	while(iter != _objList.end())
	{
		curObj = *iter;
		
		if (curObj->isDelete())
		{
			if (curObj->getType() == BaseObject::Player)
			{
				manager->loadSence<OverScene*>(new OverScene);
				return;
			}
			delete curObj;
			iter = _objList.erase(iter);
		}
		else
			++iter;
	}
	
	if (_objList.size() == 1)
	{
		if (info->isAllClear())
			manager->loadSence<ClearScene*>(new ClearScene);
		else
			manager->loadSence<WinScene*>(new WinScene);
	}
}

void GameScene::render()
{
	auto iter = _objList.begin();
	for (; iter != _objList.end(); ++iter)
		(*iter)->render(_buffer);
	
	ScreenBuffer* screen = ScreenBuffer::getInstance();
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH - 1; ++x)
		{
			if (_buffer[y][x] != ' ')
			{
				screen->Sprite_Draw(x, y, _buffer[y][x]);
				_buffer[y][x] = ' ';
			}
		}
	}

}
