#pragma once
#include "gameNode.h"
#include "GameObject.h"

class Enemy : public gameNode
{
protected:
	GameObject _obj;
public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void setPosition(vector3 pos) { _obj.pos = pos; }

	GameObject* getObj() { return &_obj; }

};

