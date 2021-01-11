#include "stdafx.h"
#include "enemyDown.h"
#include "Enemy.h"

void enemyDown::EnterState()
{
	_thisEn->SetImage();
}

void enemyDown::UpdateState()
{

	//HIT의 상태가 끝났다.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyDown::ExitState()
{
}
