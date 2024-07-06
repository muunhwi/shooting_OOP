#include "SceneManager.h"

#include "TitleScene.h"

#include "FrameCounter.h"

SceneManager SceneManager::_global;

SceneManager::SceneManager()
	: _obj{ new TitleScene }
{

}

SceneManager::~SceneManager()
{
	clear();
}

void SceneManager::sceneTrans()
{
	delete _obj;
	_obj = _next;
	_next = nullptr;
}

bool SceneManager::run()
{
	
	DWORD& stdTime = PRINT_FRAME();
	ScreenBuffer* screen = ScreenBuffer::getInstance();

	screen->Buffer_Clear();
	while (g_FixedUpdate > 0)
	{
		_obj->update();
		
		if (g_FixedUpdate > 1) 
			stdTime += FRAME_DELAY;

		g_FixedUpdate--;
		g_Frame++;
	}
	
	_obj->render();
	screen->Buffer_Flip();
	g_Render++;

	if (isSceneTrans()) 
		sceneTrans();

	if (_isExit)
		clear();
	
	return _isExit;
	
}

void SceneManager::clear()
{
	if (_next)
		delete _next;

	if (_obj)
		delete _obj;
}