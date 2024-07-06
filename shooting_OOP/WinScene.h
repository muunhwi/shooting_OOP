#pragma once

#include "SceneBase.h"
#include "UserSelectBar.h"

class WinScene : public SceneBase
{
public:
	WinScene();
	void update() override;
	void render() override;

private:
	UserSelectBar _titlePos;
	bool _isUpKeyPressed = false;
	bool _isDownKeyPressed = false;
	bool _isEnterKeyPressed = false;
};