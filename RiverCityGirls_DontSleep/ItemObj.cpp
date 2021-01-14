#include "stdafx.h"
#include "ItemObj.h"

ItemObj::ItemObj(ITEM_TYPE type, vector3 pos)
{
	_info.type = type;

	switch (type)
	{
	case ITEM_TYPE::MONEY:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("money"), pos);
		_obj.ani = new animation;
		_obj.ani->setDefPlayFrame(false, false);
		_obj.ani->setFPS(1);
		_obj.ani->init(_obj.img->getWidth(), _obj.img->getHeight(), _obj.img->getFrameWidth(), _obj.img->getFrameHeight());
		_obj.ani->start();
		_info.value = 10;
		break;
	case ITEM_TYPE::COIN:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("coin"), pos);
		_obj.ani = new animation;
		_obj.ani->setDefPlayFrame(false, true);
		_obj.ani->setFPS(1);
		_obj.ani->init(_obj.img->getWidth(), _obj.img->getHeight(), _obj.img->getFrameWidth(), _obj.img->getFrameHeight());
	    _obj.ani->start();
		_info.value = 10;
		break;
	case ITEM_TYPE::MEAT:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("meat"), pos);
		_info.value = 10;
		break;
	case ITEM_TYPE::APPLE:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("meappleat"), pos);
		_info.value = 10;
		break;
	case ITEM_TYPE::HEN:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("hen"), pos);
		_info.value = 50;
		break;
	case ITEM_TYPE::CHILI:
		_obj.init(OBJECT_GROUP::ITEM, IMG_M->findImage("chili"), pos);
		_info.value = 30;
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
	
	if (_obj.ani)
	{
		_obj.ani->frameUpdate(TIME_M->getElapsedTime() * 5);
	}
	if (_obj.ani)
	{
		_obj.ani->frameUpdate(TIME_M->getElapsedTime() * 5);
		if (!_obj.ani->isPlay())_obj.ani->start();
	}
}

void ItemObj::render()
{
	switch (getInfo().type)
	{
	case ITEM_TYPE::MONEY:
	case ITEM_TYPE::COIN:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::ANI_RENDER);
		break;
	case ITEM_TYPE::MEAT:
	case ITEM_TYPE::APPLE:
	case ITEM_TYPE::HEN:
	case ITEM_TYPE::CHILI:
		ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::RENDER);
		break;
	default:
		break;
	}

}
