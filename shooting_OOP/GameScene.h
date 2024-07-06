#pragma once
#include "SceneBase.h"
#include "MyLinkedList.h"

class GameScene : public SceneBase
{
public:
	static MyLinkedList<BaseObject*> _objList;

public:
	GameScene();
	~GameScene() override;
	void update() override;
	void render() override;

};