#include "stdafx.h"
#include "enemyRun.h"


void enemyRun::EnterState()
{
	_thisEn->getInfo().speed = _thisEn->getInfo().baseSpeed + 3;
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
}

void enemyRun::UpdateState()
{
	LookAtPlayer();

	Jump();

	if (abs(_thisEn->getPlayerAddress()->getObj().pos.x - _thisEn->getObj()->pos.x) >= 90)
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) *0, 0);
	}
	if (abs(_thisEn->getPlayerAddress()->getObj().pos.z - _thisEn->getObj()->pos.z) >= 0)
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) *0,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) *_thisEn->getInfo().speed, 0);
	
	}

	//충분히 가까워졌으면 IDLE로 돌아간다.
	if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyRun::ExitState()
{
	_thisEn->getInfo().speed = _thisEn->getInfo().baseSpeed;

}
