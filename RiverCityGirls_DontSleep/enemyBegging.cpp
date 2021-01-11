#include "stdafx.h"
#include "enemyBegging.h"
#include "Enemy.h"

void enemyBegging::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
}

void enemyBegging::UpdateState()
{
	if (TIME_M->getWorldTime() - _stateTimer > 8.0f)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyBegging::ExitState()
{
}
