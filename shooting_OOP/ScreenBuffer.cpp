#include <iostream>

#include "ScreenBuffer.h"

ScreenBuffer ScreenBuffer::_global;

void ScreenBuffer::cs_Initial(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	//-------------------------------------------------------------
	// 화면의 커서를 안보이게끔 설정한다.
	//-------------------------------------------------------------
	stConsoleCursor.bVisible = FALSE;
	stConsoleCursor.dwSize = 1;


	//-------------------------------------------------------------
	// 콘솔화면 (스텐다드 아웃풋) 핸들을 구한다.
	//-------------------------------------------------------------
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}
void ScreenBuffer::cs_Uninital(void)
{
	CONSOLE_CURSOR_INFO stConsoleCursor;

	//-------------------------------------------------------------
	// 화면의 커서를 안보이게끔 설정한다.
	//-------------------------------------------------------------
	stConsoleCursor.bVisible = TRUE;
	stConsoleCursor.dwSize = 1;


	//-------------------------------------------------------------
	// 콘솔화면 (스텐다드 아웃풋) 핸들을 구한다.
	//-------------------------------------------------------------
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(hConsole, &stConsoleCursor);
}
void ScreenBuffer::cs_MoveCursor(int iPosX, int iPosY)
{
	COORD stCoord;
	stCoord.X = iPosX;
	stCoord.Y = iPosY;
	//-------------------------------------------------------------
	// 원하는 위치로 커서를 이동시킨다.
	//-------------------------------------------------------------
	SetConsoleCursorPosition(hConsole, stCoord);
}
void ScreenBuffer::cs_ClearScreen(void)
{
	DWORD dw;

	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', 100 * 100, { 0, 0 }, &dw);
}

void ScreenBuffer::Buffer_Flip(void)
{
	int iCnt;
	for (iCnt = 0; iCnt < SCREEN_HEIGHT; iCnt++)
	{
		cs_MoveCursor(0, iCnt);
		std::cout << _screenBuffer[iCnt];
		//printf(szScreenBuffer[iCnt]);
	}
}
void ScreenBuffer::Buffer_Clear(void)
{
	int iCnt;
	memset(_screenBuffer, ' ', SCREEN_WIDTH * SCREEN_HEIGHT);

	for (iCnt = 0; iCnt < SCREEN_HEIGHT; iCnt++)
	{
		_screenBuffer[iCnt][SCREEN_WIDTH - 1] = '\0';
	}
}
void ScreenBuffer::Sprite_Draw(int iX, int iY, char chSprite)
{
	if (iX < 0 || iY < 0 || iX >= SCREEN_WIDTH - 1 || iY >= SCREEN_HEIGHT)
		return;

	_screenBuffer[iY][iX] = chSprite;
}