#include "stdafx.h"
#include "Object.h"
#include "ItemObj.h"
#include "Player.h"

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
}

void Object::render()
{
}

bool Object::isEndFrame()
{
	if (_obj.ani->getFrameIndex() >= _obj.ani->getFrameMaxIndex()) return true;
	else return false;
}

