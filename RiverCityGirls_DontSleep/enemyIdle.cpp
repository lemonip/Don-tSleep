#include "stdafx.h"
#include "enemyIdle.h"
#include "Enemy.h"
#include "Player.h"


void enemyIdle::EnterState()
{
	_thisEn->SetImage();
	_thisEn->getPlayerAddress()->getObj().pos.x;
	//_thisEn->getWalkSpeed = 2;
}

void enemyIdle::UpdateState()
{
	
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::RIGHT);
	else if(_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::LEFT);
	_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z))*2,
		-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z))*2,0);
	
}

void enemyIdle::ExitState()
{
	//_thisEn->getWalkSpeed = 2;
}
