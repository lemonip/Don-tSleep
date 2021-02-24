#pragma once
#include <vector>
//typedef void(*C_FUNCTION)(int);		//�Լ� ������

#include <functional>
typedef std::function<void(void)> CALLBACKFUCN;	//��ų�

enum class BUTTONSTATE
{
	NONE, DOWN, UP
};

struct BINGO
{
	RECT rc;
	int bingo[4][2];
};

/*====================================================================
						�� ư
====================================================================*/
class Button
{
public:

	BINGO _bingo;

	const char* _name;
	BUTTONSTATE _state;

	image* _none;
	image* _down;
	image* _up;

	vector3 _pos;
	RECT _rc;

	bool _isSelect;

	CALLBACKFUCN funcp;
	int _param;
	Interpolation* _inter;

public:
	Button(image* _none, image* down, image* up, vector3 pos, CALLBACKFUCN fp, int param);
	Button(image* down, image* up, vector3 pos, CALLBACKFUCN fp, int param);
	~Button() {};

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
};

/*====================================================================
						�� ��
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

