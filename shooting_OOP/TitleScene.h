#pragma once
#include "SceneBase.h"
#include "UserSelectBar.h"

class TitleScene : public SceneBase
{
public:
	TitleScene();
	void update() override;
	void render() override;

private:
	UserSelectBar _titlePos;
	bool _isUpKeyPressed = false;
	bool _isDownKeyPressed = false;
	bool _isEnterKeyPressed = false;
};
