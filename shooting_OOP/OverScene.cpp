#include <iostream>
#include <windows.h>

#include "SceneManager.h"
#include "StageInfo.h"
#include "FrameCounter.h"

#include "OverScene.h"

#include "LoadScene.h"
#include "TitleScene.h"

#undef TRY_AGAIN

constexpr unsigned long TRY_AGAIN = 10;
constexpr unsigned long EXIT = 11;

class OverFuctor : public UserSelectBar::EnterKeyFuctor
{
public:
	void operator()(UserSelectBar& userBar)
	{
		SceneManager* manager = SceneManager::getInstance();
		if (userBar._ypos == TRY_AGAIN)
			manager->loadSence<LoadScene*>(new LoadScene);
		else
			manager->exit();
	}
};



OverScene::OverScene()
	: _titlePos{TRY_AGAIN, EXIT, new OverFuctor }
{
	bufferClear();
	const char* one = "GAVE OVER";
	const char* two = "TRY AGAIN?";
	const char* three = "EXIT";

	strncpy_s(_buffer[8] + 34, SCREEN_WIDTH - 34, one, strlen(one));
	strncpy_s(_buffer[10] + 35, SCREEN_WIDTH - 35, two, strlen(two));
	strncpy_s(_buffer[11] + 35, SCREEN_WIDTH - 35, three, strlen(three));
	
};


void OverScene::update()
{
	_titlePos.upKeyPress();
	_titlePos.downKeyPress();
	_titlePos.enterKeyPress();
}

void OverScene::render()
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