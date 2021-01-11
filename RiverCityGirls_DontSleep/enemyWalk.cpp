#include "stdafx.h"
#include "enemyWalk.h"


void enemyWalk::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
	
}

void enemyWalk::UpdateState()
{
	LookAtPlayer();
	Jump();

    //x 움직임
	if (abs(_thisEn->getPlayerAddress()->getObj().pos.x - _thisEn->getObj()->pos.x) >= 90)
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * 0, 0);
	}
	//z 움직임
	if (abs(_thisEn->getPlayerAddress()->getObj().pos.z - _thisEn->getObj()->pos.z) >= 0)
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * 0,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) *_thisEn->getInfo().speed, 0);
	}

	//충분히 가까워졌으면 IDLE로 돌아간다.
	if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
	/*
	for (int i = 1; i < 100; i++)
	{
		if (TIME_M->getWorldTime() - _stateTimer >= i*2)
		{
			_a1 = _thisEn->getObj()->pos.x;
		}
		if (TIME_M->getWorldTime() - _stateTimer >= i*2 - 1)
		{
			_a2 = _thisEn->getObj()->pos.x;
		}
	}
	if (_a1 == _a2)
	{
		_thisEn->xzyMove(0, 2, 0);
	}
	else if (_a1 != _a2)
	{
		if (abs(_thisEn->getPlayerAddress()->getObj().pos.x - _thisEn->getObj()->pos.x) >= 90)
		{
			_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed,
				-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * 0, 0);
		}
		//z 움직임
		if (abs(_thisEn->getPlayerAddress()->getObj().pos.z - _thisEn->getObj()->pos.z) >= 0)
		{
			_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * 0,
				-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) *_thisEn->getInfo().speed, 0);
		}
	}

	*/
}

void enemyWalk::ExitState()
{
}
