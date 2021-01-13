#include "stdafx.h"
#include "Object.h"
#include "ItemObj.h"

HRESULT Object::init()
{
	return S_OK;
}

void Object::release()
{
}

void Object::update()
{
	_obj.update();
	if (_obj.ani)
	{
		_obj.ani->frameUpdate(TIME_M->getElapsedTime() * 5);
	}
}

void Object::render()
{
}

