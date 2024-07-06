#pragma once
#include <windows.h>
#define SCREEN_WIDTH		81		// �ܼ� ���� 80ĭ + NULL
#define SCREEN_HEIGHT		24		// �ܼ� ���� 24ĭ


class ScreenBuffer
{
public:
	static ScreenBuffer* getInstance() { return &_global; }
	
	void Buffer_Flip(void);
	void Buffer_Clear(void);
	void Sprite_Draw(int iX, int iY, char chSprite);

	void cs_Initial(void);
	void cs_Uninital(void);
	void cs_MoveCursor(int iPosX, int iPosY);
	void cs_ClearScreen(void);

private:
	static ScreenBuffer _global;
private:
	HANDLE hConsole;
	char _screenBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
	ScreenBuffer() { cs_Initial(); }
};