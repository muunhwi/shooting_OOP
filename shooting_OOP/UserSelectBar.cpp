#include "FrameCounter.h"
#include "UserSelectBar.h"


UserSelectBar::UserSelectBar(int top, int bottom, EnterKeyFuctor* fuctor, char shape, int xpos, int ypos)
	: _top{ top }, _bottom{ bottom }, _fuctor{ fuctor }, _shape{ shape }, _xpos{ xpos }, _ypos{ ypos } {}

UserSelectBar::~UserSelectBar(){ delete _fuctor; }

void UserSelectBar::upKeyPress()
{
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (!_isUpKeyPressed && (timeGetTime() - g_keyPressedTime >= INPUT_WAIT))
		{
			_isUpKeyPressed = true;
			g_keyPressedTime = timeGetTime();

			if (_ypos > _top)
				_ypos--;
		}
		else
			_isUpKeyPressed = false;
	}
}

void UserSelectBar::downKeyPress()
{
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (!_isDownKeyPressed && (timeGetTime() - g_keyPressedTime >= INPUT_WAIT))
		{
			_isDownKeyPressed = true;
			g_keyPressedTime = timeGetTime();

			if (_ypos < _bottom)
				_ypos++;
		}
		else
			_isDownKeyPressed = false;
	}
}

void UserSelectBar::enterKeyPress()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (!_isEnterKeyPressed && timeGetTime() - g_keyPressedTime >= INPUT_WAIT)
		{
			g_keyPressedTime = timeGetTime();
			(*_fuctor)(*this);
		}
		else
			_isEnterKeyPressed = false;
	}
}