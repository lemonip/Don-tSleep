#pragma once
#include <vector>
//typedef void(*CALLBACK_FUNCTION)(void);		//함수 포인터

typedef void(*CALLBACK_FUNCTION)(void);		//함수 포인터

#include <functional>
typedef std::function<void(void)> CALLBACKFUCN;

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

	CALLBACK_FUNCTION funcp;
	Interpolation* _inter;

public:
	Button(image* _none, image* down, image* up, vector3 pos, CALLBACK_FUNCTION fp);
	Button(image* down, image* up, vector3 pos, CALLBACK_FUNCTION fp);
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

	void release();
	bool update();
	void render(HDC hdc);

	void addButton(Button button);
	
};

