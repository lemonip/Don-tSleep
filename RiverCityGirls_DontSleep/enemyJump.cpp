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
	if (_thisEn->getObj()->pos.y > 0)
	{
		_thisEn->getObj()->pos.y = 0;
	}
	if (_thisEn->getObj()->pos.y == 0)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
	
}

void enemyJump::ExitState()
{
	_thisEn->getInfo().jumpPower = 0;
	_thisEn->getInfo().isSky = false;
}

