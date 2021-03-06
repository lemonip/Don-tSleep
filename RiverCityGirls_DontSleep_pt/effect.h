#pragma once
#include "gameNode.h"

class animation;

class effect : public gameNode
{
protected:
	int _x, _y;

	image* _effectImage;
	animation* _effectAnimation;
	bool _isRunning;
	float _elapsedTime;

public:
	effect();
	~effect();

	virtual HRESULT init(image* effectImage, int frameW, int frameH, int fps, float elapsedTime);
	virtual void release();
	virtual void update();
	virtual void render();

	void startEffect(int x, int y);

	virtual void killEffect();

	bool getIsRunning() { return _isRunning; }
};

