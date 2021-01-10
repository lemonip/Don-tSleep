#include "stdafx.h"
#include "Object.h"

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
