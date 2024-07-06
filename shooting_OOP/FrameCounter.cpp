#include <iostream>
#include "FrameCounter.h"

DWORD& PRINT_FRAME()
{
	static DWORD startTime = timeGetTime();
	static DWORD stdTime = timeGetTime();
	DWORD dwTime = timeGetTime() - stdTime;

	if (dwTime < FRAME_DELAY)
		Sleep(FRAME_DELAY - dwTime);
	stdTime += FRAME_DELAY;

	DWORD curTime = timeGetTime();
	if (curTime - startTime >= 1000)
	{
		std::cout << "FRAME " << g_Frame << '\n';
		std::cout << "RANDER " << g_Render << '\n';
		g_Frame = 0;
		g_Render = 0;
		startTime += 1000;
	}

	g_FixedUpdate = ((curTime - stdTime) / FRAME_DELAY) + 1;

	return stdTime;
}


const unsigned long INPUT_WAIT = 150;
const unsigned long FRAME_DELAY = 50;

unsigned long g_keyPressedTime = 0;
unsigned long g_FixedUpdate = 0;
unsigned long g_Frame = 0;
unsigned long g_Render = 0;
