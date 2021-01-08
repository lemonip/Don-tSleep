#include "stdafx.h"
#include "schoolGirl.h"
#include "Player.h"

#include "enemyIDLE.h"


HRESULT schoolGirl::init()
{
	Enemy::init();
	                        
	_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirlIdle"),_obj.pos);
	_ENEMY_TYPE = ENEMY_TYPE::SCHOOLGIRL;
	SetState(EN_STATE::EN_IDLE);
	

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
