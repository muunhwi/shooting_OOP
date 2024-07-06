#include <iostream>

#include "SceneManager.h"
#include "StageInfo.h"
#include "FrameCounter.h"

#include "LoadScene.h"
#include "GameScene.h"

LoadScene::LoadScene()
	:_isLoad { false }
{
	bufferClear();
	const char* one = "SHOOTING GAME";
	const char* two = "==LOADING==";

	strncpy_s(_buffer[8] + 34, SCREEN_WIDTH - 34, one, strlen(one));
	strncpy_s(_buffer[10] + 35, SCREEN_WIDTH - 35, two, strlen(two));
}

void LoadScene::update()
{
	if (!_isLoad)
	{
		StageInfo* info = StageInfo::getInstance();
		SceneManager* manager = SceneManager::getInstance();

		if (!info->isLoadStage())
		{
			bool isOk = info->loadStage();

			if (!isOk)
			{
				manager->exit();
				return;
			}
				
		}
		manager->loadSence<GameScene*>(new GameScene);
		_isLoad = true;
	}
}

void LoadScene::render()
{
	ScreenBuffer* screen = ScreenBuffer::getInstance();
	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH - 1; ++x)
			screen->Sprite_Draw(x, y, _buffer[y][x]);
	}
}