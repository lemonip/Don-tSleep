#include "stdafx.h"
#include "enemyWalk.h"


void enemyWalk::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
	
}

void enemyWalk::UpdateState()
{
	/*
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::RIGHT);
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::LEFT);
	_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed ,
		-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) *_thisEn->getInfo().speed, 0);
	if (_thisEn->getPlayerAddress()->getObj().pos.y < _thisEn->getObj()->pos.y && !_thisEn->getPlayerAddress()->getInfo().isSky)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 50)
		{
			_thisEn->SetState(EN_STATE::EN_JUMP);
		}
	}
	if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 100
		&& _thisEn->getObj()->pos.z >= _thisEn->getPlayerAddress()->getObj().shadow.RT.z && _thisEn->getObj()->pos.z <= _thisEn->getPlayerAddress()->getObj().shadow.RB.z)
	{
		_thisEn->SetState(EN_STATE::EN_ATTACK1);
	}
	if (TIME_M->getWorldTime() - _stateTimer > 7.f)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
	*/
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::RIGHT);
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::LEFT);
	if (abs(_thisEn->getPlayerAddress()->getObj().pos.x - _thisEn->getObj()->pos.x) > 50)
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * 0, 0);
	}
	if (abs(_thisEn->getPlayerAddress()->getObj().pos.z - _thisEn->getObj()->pos.z) > 20)
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * 0,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) *_thisEn->getInfo().speed, 0);
	}
	if (_thisEn->getPlayerAddress()->getObj().pos.y < _thisEn->getObj()->pos.y && !_thisEn->getPlayerAddress()->getInfo().isSky)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 50)
		{
			_thisEn->SetState(EN_STATE::EN_JUMP);
		}
	}
	if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 100
		&& _thisEn->getObj()->pos.z >= _thisEn->getPlayerAddress()->getObj().shadow.RT.z && _thisEn->getObj()->pos.z <= _thisEn->getPlayerAddress()->getObj().shadow.RB.z)
	{
		_thisEn->SetState(EN_STATE::EN_ATTACK1);
	}
	if (TIME_M->getWorldTime() - _stateTimer > 7.f)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
	if (abs(_thisEn->getPlayerAddress()->getObj().pos.z - _thisEn->getObj()->pos.z) <= 20 && abs(_thisEn->getPlayerAddress()->getObj().pos.x - _thisEn->getObj()->pos.x) <= 100)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyWalk::ExitState()
{
}
