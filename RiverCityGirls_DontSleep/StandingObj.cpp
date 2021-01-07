#include "stdafx.h"
#include "StandingObj.h"

StandingObj::StandingObj(OBJECT_TYPE type, vector3 pos)
{
	switch (type)
	{
		case OBJECT_TYPE::DESK:
			_obj.init(OBJECT_GROUP::OBJECT, OBJECT_TYPE::DESK, IMG_M->findImage("desk"), pos, 70); //58
			_type = type;
		break;
		case OBJECT_TYPE::LEFTWALL:

			break;
		default:
		break;
	}
}

HRESULT StandingObj::init()
{
	return S_OK;
}

void StandingObj::release()
{
}

void StandingObj::update()
{
}

void StandingObj::render()
{
	switch (_type)
	{
	case OBJECT_TYPE::DESK:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);

		break;
	default:
		break;
	}

}
