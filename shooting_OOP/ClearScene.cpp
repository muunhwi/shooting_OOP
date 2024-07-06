#include <windows.h>

#include "SceneManager.h"
#include "StageInfo.h"
#include "FrameCounter.h"

#include "TitleScene.h"
#include "ClearScene.h"


constexpr unsigned long TITLE = 10;
constexpr unsigned long EXIT  = 11;

class ClearFuctor : public UserSelectBar::EnterKeyFuctor
{
public:
	void operator()(UserSelectBar& userBar)
	{
		SceneManager* manager = SceneManager::getInstance();
		if (userBar._ypos == TITLE)
			manager->loadSence<TitleScene*>(new TitleScene);
		else
			manager->exit();
	}
};

ClearScene::ClearScene()
	: _titlePos{TITLE, EXIT, new ClearFuctor}
{
	bufferClear();
	const char* one   = "ALL STAGE CLEAR!";
	const char* two   = "TITLE";
	const char* three = "EXIT";

	strncpy_s(_buffer[8] + 34, SCREEN_WIDTH - 34, one, strlen(one));
	strncpy_s(_buffer[10] + 35, SCREEN_WIDTH - 35, two, strlen(two));
	strncpy_s(_buffer[11] + 35, SCREEN_WIDTH - 35, three, strlen(three));
	_buffer[_titlePos._ypos][_titlePos._xpos] = _titlePos._shape;
};


void ClearScene::update()
{
	_titlePos.upKeyPress();
	_titlePos.downKeyPress();
	_titlePos.enterKeyPress();
}

void ClearScene::render()
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

