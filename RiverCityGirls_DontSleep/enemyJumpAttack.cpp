#include "stdafx.h"
#include "enemyJumpAttack.h"
#include "Enemy.h"

void enemyJumpAttack::EnterState()
{
	_thisEn->SetImage();
	_thisEn->getInfo().jumpPower = JUMPPOWERVALUE;
	_thisEn->getInfo().isSky = true;
}

void enemyJumpAttack::UpdateState()
{
	_thisEn->getObj()->pos.y -= _thisEn->getInfo().jumpPower;
	_thisEn->getInfo().jumpPower -= GRAVITYVALUE;
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::RIGHT);
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::LEFT);
	if (_thisEn->getdest() == DIRECTION::RIGHT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.right, _thisEn->getObj()->rc.top, 100, 200);
	} 
	else if (_thisEn->getdest() == DIRECTION::LEFT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.left - 100, _thisEn->getObj()->rc.top, 100, 200);
	}
	if (_thisEn->getObj()->pos.y > 0)
	{
		_thisEn->getObj()->pos.y = 0;
	}
	if (_thisEn->getObj()->pos.y == 0)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
	
}

void enemyJumpAttack::ExitState()
{
	_thisEn->getInfo().jumpPower = 0;
	_thisEn->getInfo().isSky = false;
}
