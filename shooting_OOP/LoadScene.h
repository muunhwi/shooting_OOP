#pragma once
#include "SceneBase.h"

class LoadScene : public SceneBase
{	
public:
	LoadScene();

	void update() override;
	void render() override;
private:
	bool _isLoad;
};