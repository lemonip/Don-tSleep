#include "stdafx.h"
#include "ObjectManager.h"
#include "AllObjects.h"

HRESULT ObjectManager::init()
{
	return S_OK;
}

void ObjectManager::release()
{
	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->release();
		delete _vObject[i];
	}
	_vObject.clear();
}

void ObjectManager::update()
{

	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->update();
	}
}

void ObjectManager::render()
{
	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->render();
	}

	for (int i = 0; i < _vObject.size(); i++)
	{
		_vObject[i]->getObj()->PolyLineRender(getMapDC());
	}
}

void ObjectManager::pushObject(OBJECT_TYPE type, vector3 pos)
{
	switch (type)
	{
	case OBJECT_TYPE::DESK:
		_vObject.push_back(new StandingObj(type, pos));
		break;
	case OBJECT_TYPE::TABLE:
		_vObject.push_back(new StandingObj(type, pos));
		break;
	case OBJECT_TYPE::VENDINGMACHINE:
		_vObject.push_back(new BrokenObj(type, pos));
		break;
	case OBJECT_TYPE::LADDER:
		_vObject.push_back(new StandingObj(type, pos));
		break;
	default:
		break;
	}
}

void ObjectManager::pushItem(ITEM_TYPE type, vector3 pos)
{
	switch (type)
	{
	case ITEM_TYPE::MONEY:
		break;
	case ITEM_TYPE::COIN:
		break;
	case ITEM_TYPE::MEAT:
		_vObject.push_back(new ItemObj(type, pos));
		break;
	default:
		break;
	}
}

void ObjectManager::pushWeapon(WEAPON_TYPE type, vector3 pos)
{
	switch (type)
	{
	case WEAPON_TYPE::TRASHCAN:
		break;
	case WEAPON_TYPE::BASEBALL:
		break;
	default:
		break;
	}
}

