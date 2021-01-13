#include "stdafx.h"
#include "ItemObj.h"

ItemObj::ItemObj(ITEM_TYPE type, vector3 pos)
{
	_info.type = type;

	switch (type)
	{
	case ITEM_TYPE::MONEY:
		break;
	case ITEM_TYPE::COIN:
		break;
	case ITEM_TYPE::MEAT:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("meat"), pos);
		_info.healValue = 10;
		break;
	case ITEM_TYPE::APPLE:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("meappleat"), pos);
		_info.healValue = 10;
		break;
	case ITEM_TYPE::HEN:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("hen"), pos);
		_info.healValue = 50;
		break;
	case ITEM_TYPE::CHILI:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("chili"), pos);
		_info.healValue = 30;
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
