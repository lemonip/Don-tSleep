#pragma once

enum class UITYPE;

/*====================================================================
						단일 이미지 UI
====================================================================*/
class UI
{
public:
	UITYPE _type;
	image* _img;

	vector3* _pos;
	vector3 _goal;
	float _speed;
	RECT _rc;

	bool _isActive;
	bool _isMove;

	int _alpha;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);

	void setActive(bool active) { _isActive = active; }
	void setPos(vector3* pos) { _pos = pos; }
	void setPos(vector3 pos) { *_pos = pos; }

	void setAlpha(int alpha) { _alpha = alpha; }
	int getAlpha() { return _alpha; }
	void changeImg(string imgName);
};

/*====================================================================
						Progress Bar UI
====================================================================*/
class Bar : public UI
{
private:
	image* _back;
	image* _front;
	float _ratio;
	int* _current, *_max;

public:
	Bar(image* front, image* back, int* current, int* max);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};

/*====================================================================
						O P T I O N
====================================================================*/
class Option : public UI
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};

/*====================================================================
						C A L L   P H O N E
====================================================================*/
class CallPhone : public UI
{
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	void render(HDC hdc);
};

/*====================================================================
						S T A G E	D O O R
====================================================================*/

class StageDoor : public UI
{

public:
	StageDoor(int alpha);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
};