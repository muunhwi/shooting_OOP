#include <iostream>
#include <windows.h>

#include "SceneManager.h"
#include "StageInfo.h"
#include "FrameCounter.h"

#include "WinScene.h"
#include "LoadScene.h"
#include "ClearScene.h"
#include "TitleScene.h"


constexpr unsigned long NEXT_STAGE = 10;
constexpr unsigned long EXIT = 11;

class WinFuctor : public UserSelectBar::EnterKeyFuctor
{
public:
	void operator()(UserSelectBar& userBar)
	{
		StageInfo* info = StageInfo::getInstance();
		SceneManager* manager = SceneManager::getInstance();

		if (userBar._ypos == NEXT_STAGE)
		{
			info->increaseStageLevel();
			manager->loadSence<LoadScene*>(new LoadScene);
		}
		else
			manager->exit();
	}
};


WinScene::WinScene()
	: _titlePos{NEXT_STAGE, EXIT, new WinFuctor }
{
	bufferClear();
	const char* one = "YOU WIN";
	const char* two = "NEXT STAGE";
	const char* three = "EXIT";

	strncpy_s(_buffer[8] + 34, SCREEN_WIDTH - 34, one, strlen(one));
	strncpy_s(_buffer[10] + 35, SCREEN_WIDTH - 35, two, strlen(two));
	strncpy_s(_buffer[11] + 35, SCREEN_WIDTH - 35, three, strlen(three));
};


void WinScene::update()
{
	StageInfo* info = StageInfo::getInstance();
	SceneManager* manager = SceneManager::getInstance();

	if (info->isAllClear())
	{
		manager->loadSence<ClearScene*>(new ClearScene);
	}
	else
	{
		_titlePos.upKeyPress();
		_titlePos.downKeyPress();
		_titlePos.enterKeyPress();
	}
}

void WinScene::render()
{
	_buffer[_titlePos._ypos][_titlePos._xpos] = _titlePos._shape;

	ScreenBuffer* screen = ScreenBuffer::getInstance();

	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		for (int x = 0; x < SCREEN_WIDTH - 1; ++x)
			screen->Sprite_Draw(x, y, _buffer[y][x]);
	}
	
	_buffer[_titlePos._ypos][_titlePos._xpos] = ' ';
}

