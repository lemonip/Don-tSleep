#include "stdafx.h"
#include "Enemy.h"

HRESULT Enemy::init()
{
	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
	_obj.update();

}

void Enemy::render()
{
}
