#include "stdafx.h"
#include "enemyGuard.h"
#include "Enemy.h"

void enemyGuard::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
}

void enemyGuard::UpdateState()
{
	if (TIME_M->getWorldTime() - _stateTimer > 2.0f)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyGuard::ExitState()
{
	Damage(_thisEn->getPlayerAddress()->getInfo().force / 2);
}
