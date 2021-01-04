#pragma once
#include "Object.h"
class ItemObj : public Object
{
public:
	ItemObj(ITEM_TYPE type, vector3 pos);

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

