#pragma once
#include <iostream>
#include <type_traits>

#include "SceneBase.h"



class SceneManager
{
public:
	static SceneManager* getInstance() { return &_global; }
public:

	template<typename T, typename = std::enable_if<std::is_base_of<SceneBase, T>::value>>
	void loadSence(SceneBase* obj) { _next = static_cast<T>(obj); }
	bool isSceneTrans() const { return _next ? true : false; }
	void exit() { _isExit = true; }

	bool run();
	void clear();
	void sceneTrans();

private:
	SceneManager();
	~SceneManager();

private:
	static SceneManager _global;

private:
	SceneBase* _obj;
	SceneBase* _next = nullptr ;
	bool _isExit = false;
};