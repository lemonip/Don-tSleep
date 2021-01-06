#pragma once
#include "gameNode.h"
#include "GameObject.h"

class Object : public gameNode
{
protected:
	GameObject _obj;
	OBJECT_TYPE _type;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	GameObject* getObj() { return &_obj; }
};

