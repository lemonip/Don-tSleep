#pragma once
#include "Scene.h"
class SelectScene : public Scene
{
private:
	vector3 loop;

	image* _illust;
	vector3 _illustPos;
	Interpolation* _illustInter;

	float _ratioOffset;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

