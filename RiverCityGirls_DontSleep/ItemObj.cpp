#include "stdafx.h"
#include "ItemObj.h"

ItemObj::ItemObj(ITEM_TYPE type, vector3 pos)
{
	switch (type)
	{
	case ITEM_TYPE::MONEY:
		break;
	case ITEM_TYPE::COIN:
		break;
	case ITEM_TYPE::MEAT:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("meat"), pos);

		break;
	default:
		break;
	}
}

HRESULT ItemObj::init()
{
	return S_OK;
}

void ItemObj::release()
{
}

void ItemObj::update()
{
}

void ItemObj::render()
{
	ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);

}
