#pragma once
#include "SceneBase.h"

#include "UserSelectBar.h"

class ClearScene : public SceneBase
{
public:
	ClearScene();

	void update() override;
	void render() override;

private:
	UserSelectBar _titlePos;

};
