#pragma once
#include "BaseObject.h"
class SceneBase
{
public:
	virtual void update() = 0;
	virtual void render() = 0;
	virtual ~SceneBase() {}

	void bufferClear()
	{
		for (int i = 0; i < SCREEN_HEIGHT; ++i)
		{
			for (int j = 0; j < SCREEN_WIDTH - 1; ++j)
				_buffer[i][j] = ' ';

			_buffer[i][SCREEN_WIDTH - 1] = '\0';
		}
	}

protected:
	char _buffer[SCREEN_HEIGHT][SCREEN_WIDTH];
};