#pragma once
struct UserSelectBar
{
	struct EnterKeyFuctor
	{
		virtual void operator()(UserSelectBar& userBar) = 0;
	};

	char _shape;
	bool _isUpKeyPressed = false;
	bool _isDownKeyPressed = false;
	bool _isEnterKeyPressed = false;
	int _xpos;
	int _ypos;
	int _top;
	int _bottom;
	EnterKeyFuctor* _fuctor;

	UserSelectBar(int top, int bottom, EnterKeyFuctor* fuctor, char shape = '>', int xpos = 34, int ypos = 10);
	~UserSelectBar();

	void upKeyPress();
	void downKeyPress();
	void enterKeyPress();

};

