#include "stdafx.h"
#include "enemyJump.h"
#include "Enemy.h"

void enemyJump::EnterState()
{
	_thisEn->SetImage();
	_thisEn->getInfo().jumpPower = JUMPPOWERVALUE;
	_thisEn->getInfo().isSky = true;
}

void enemyJump::UpdateState()
{
	
	_thisEn->getObj()->pos.y -= _thisEn->getInfo().jumpPower;
	_thisEn->getInfo().jumpPower -= GRAVITYVALUE;
	
	
	if (_thisEn->getdest() == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x >= _thisEn->getObj()->img->getMaxFrameX())
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed, 0);
	}
	else if (_thisEn->getdest() == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x <= 0)
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed, 0);
	}
	
	
	if (_thisEn->getObj()->pos.y > 0)
	{
		_thisEn->getObj()->pos.y = 0;
	}
	if (_thisEn->getObj()->pos.y == 0)
	{
		_thisEn->SetState(EN_STATE::EN_WALK);
	}
	if (_thisEn->getPlayerAddress()->getObj().pos.y == 0 && !_thisEn->getPlayerAddress()->getInfo().isSky)
	{
		_thisEn->SetState(EN_STATE::EN_JUMPATTACK);
	}
}

void enemyJump::ExitState()
{
	_thisEn->getInfo().jumpPower = 0;
	_thisEn->getInfo().isSky = false;
}

