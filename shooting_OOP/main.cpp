#include "SceneManager.h"
#pragma comment(lib, "winmm.lib")

int main()
{
	SceneManager* scene = SceneManager::getInstance();

	timeBeginPeriod(1);
	while (1)
	{ 
		if (scene->run())
			break;
	}
	timeEndPeriod(1);

	return 0;

}

