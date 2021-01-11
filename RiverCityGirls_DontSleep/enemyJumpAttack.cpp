#include "stdafx.h"
#include "enemyJumpAttack.h"
#include "Enemy.h"

void enemyJumpAttack::EnterState()
{
	_thisEn->SetImage();
	_thisEn->getInfo().isSky = true;
}

void enemyJumpAttack::UpdateState()
{
	_thisEn->getObj()->pos.y -= _thisEn->getInfo().jumpPower;
	_thisEn->getInfo().jumpPower -= GRAVITY;

	LookAtPlayer();

	Attack();

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
	_thisEn->getInfo().isAttack = false;
}
