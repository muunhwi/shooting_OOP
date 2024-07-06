#include <iostream>
#include <windows.h>

#include "SceneManager.h"
#include "StageInfo.h"
#include "FrameCounter.h"

#include "TitleScene.h"
#include "LoadScene.h"

constexpr unsigned long GAME_START = 10;
constexpr unsigned long EXIT = 11;

class TitleFuctor : public UserSelectBar::EnterKeyFuctor
{
public:
	void operator()(UserSelectBar& userBar)
	{
		SceneManager* manager = SceneManager::getInstance();

		if (userBar._ypos == GAME_START)
			manager->loadSence<LoadScene*>(new LoadScene);
		else
			manager->exit();
	}
};


TitleScene::TitleScene() 
	: _titlePos{GAME_START, EXIT, new TitleFuctor }
{
	bufferClear();
	const char* one    = "SHOOTING GAME";
	const char* two    = "GAME START";
	const char* three  = "EXIT";
	const char* four   = "menu select enter key";
	const char* five   = "menu move arrows keys";
	const char* six    = "attack z key";
	const char* seven  = "reverse attack x key";

	strncpy_s(_buffer[8] + 34, SCREEN_WIDTH - 34, one, strlen(one));
	strncpy_s(_buffer[10] + 35, SCREEN_WIDTH - 35, two, strlen(two));
	strncpy_s(_buffer[11] + 35, SCREEN_WIDTH - 35, three, strlen(three));
	strncpy_s(_buffer[12] + 35, SCREEN_WIDTH - 35, four, strlen(four));
	strncpy_s(_buffer[13] + 35, SCREEN_WIDTH - 35, five, strlen(five));
	strncpy_s(_buffer[14] + 35, SCREEN_WIDTH - 35, six, strlen(six));
	strncpy_s(_buffer[15] + 35, SCREEN_WIDTH - 35, seven, strlen(seven));
};


void TitleScene::update() 
{
	_titlePos.upKeyPress();
	_titlePos.downKeyPress();
	_titlePos.enterKeyPress();
}

void TitleScene::render()
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