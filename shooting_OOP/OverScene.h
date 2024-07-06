#pragma once
#include "SceneBase.h"
#include "UserSelectBar.h"

class OverScene : public SceneBase
{
public:
	OverScene();

	void update() override;
	void render() override;

private:
	UserSelectBar _titlePos;
	bool _isUpKeyPressed = false;
	bool _isDownKeyPressed = false;
	bool _isEnterKeyPressed = false;
};