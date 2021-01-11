#include "stdafx.h"
#include "schoolBoy.h"
#include "Player.h"



HRESULT schoolBoy::init()
{
	Enemy::init();

	_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolBoyIdle"), _obj.pos);
	_ENEMY_TYPE = ENEMY_TYPE::SCHOOLBOY;
	SetState(EN_STATE::EN_IDLE);
	return S_OK;
}

void schoolBoy::release()
{
}

void schoolBoy::update()
{
	Enemy::update();
}
