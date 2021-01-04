#include "stdafx.h"
#include "schoolGirl.h"
#include "Player.h"

#include "enemyIDLE.h"


HRESULT schoolGirl::init()
{

	_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirlIdle"),_obj.pos);

	SetState(EN_STATE::EN_IDLE);
	_dest = DIRECTION::RIGHT;


	return S_OK;
}

void schoolGirl::release()
{

}

void schoolGirl::update()
{
	//Enemy::update();
	//_EState->UpdateState();
	//SetState(EN_STATE::EN_IDLE);
}

void schoolGirl::render()
{

}
