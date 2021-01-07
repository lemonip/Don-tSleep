#pragma once
#include "Object.h"
class BrokenObj : public Object
{
private:
	int _frameIdx;

public:
	BrokenObj(OBJECT_TYPE type, vector3 pos);

	virtual HRESULT init();

	virtual void release();
	virtual void update();
	virtual void render();
};