#include "stdafx.h"
#include "schoolGirl.h"

HRESULT schoolGirl::init()
{

	_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirl"),_obj.pos);

	return S_OK;
}

void schoolGirl::release()
{

}

void schoolGirl::update()
{
	Enemy::update();
}

void schoolGirl::render()
{

}
