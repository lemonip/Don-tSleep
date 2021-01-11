#include "stdafx.h"
#include "enemyStun.h"
#include "Enemy.h"

void enemyStun::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
}

void enemyStun::UpdateState()
{
	if(TIME_M->getWorldTime() - _stateTimer > 3.0f)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyStun::ExitState()
{
}
