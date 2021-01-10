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
		if (_vObject[i]->getObj()->isRender) _vObject[i]->update();
	}
}

void ObjectManager::render()
{
	for (int i = 0; i < _vObject.size(); i++)
	{
		if (_vObject[i]->getObj()->isRender) _vObject[i]->render();
		if (_vObject[i]->getObj()->isRender) _vObject[i]->getObj()->PolyLineRender(getMapDC());
	}
}

Object * ObjectManager::findHardPlatform()
{
	if (_vObject.empty() == false)
	{
		for (int i = 0; i < _vObject.size(); ++i)
		{
			if (_vObject[i]->getObj()->type == OBJECT_TYPE::HARDPLATFORM)
			{
				return _vObject[i];
			}
		}
	}
	else return nullptr;
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
	case OBJECT_TYPE::HARDPLATFORM:
		_vObject.push_back(new StandingObj(type, pos));
		break;
	case OBJECT_TYPE::PILLAR_LEFT: case OBJECT_TYPE::PILLAR_BIG_LEFT:
		_vObject.push_back(new BrokenObj(type, pos));
		break;
	case OBJECT_TYPE::PILLAR_RIGHT: case OBJECT_TYPE::PILLAR_BIG_RIGHT:
		_vObject.push_back(new BrokenObj(type, pos));
		break;
	default:
		break;
	}
}

void ObjectManager::pushItem(ITEM_TYPE type, vector3 pos)
{
	_vObject.push_back(new ItemObj(type, pos));
}

void ObjectManager::pushWeapon(WEAPON_TYPE type, vector3 pos)
{
	_vObject.push_back(new Weapon(type, pos));

}

void ObjectManager::popObject(int index)
{
	for (int i = 0; i < _vObject.size();)
	{
		if (i == index)
		{
			_vObject.erase(_vObject.begin() + i);
		}
		else  i++;
	}
}

