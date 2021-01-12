#pragma once
#include "gameNode.h"
#include "GameObject.h"


class Object : public gameNode
{
protected:
	GameObject _obj;
	OBJECT_TYPE _type;
	float _renderTimer;


public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	float getTimer() { return _renderTimer; }
	void setTimer(float time) { _renderTimer = time; }
	GameObject* getObj() { return &_obj; }
};

