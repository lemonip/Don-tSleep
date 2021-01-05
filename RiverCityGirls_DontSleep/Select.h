#pragma once
#include <vector>
typedef void(*CALLBACK_FUNCTION)(void);

enum class BUTTONSTATE
{
	NONE, DOWN, UP
};

/*====================================================================
						버 튼
====================================================================*/
class Button
{
public:
	const char* _name;
	BUTTONSTATE _state;

	image* _none;
	image* _down;
	image* _up;

	vector3 _pos;
	RECT _rc;

	bool _isSelect;

	CALLBACK_FUNCTION _callback;
	Interpolation* _inter;

public:
	Button(image* _none, image* down, image* up, vector3 pos, CALLBACK_FUNCTION cbFunction);
	Button(image* down, image* up, vector3 pos, CALLBACK_FUNCTION cbFunction);
	~Button() {};

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

/*====================================================================
						선 택
====================================================================*/
class Select
{
public:
	Select() { _index = 0;}
	~Select() {}

	vector<Button*> _vButton;

	int _index;
	float _selectTime;

	HRESULT init();
	void release();
	bool update();
	void render(HDC hdc);

	void addButton(Button button);
	
};

