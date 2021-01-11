#include "stdafx.h"
#include "enemyHit.h"
#include "Enemy.h"


void enemyHit::EnterState()
{
	_thisEn->SetImage();
	Damage(_thisEn->getPlayerAddress()->getInfo().force);
	if (_thisEn->getPlayerAddress()->getInfo().state == PL_STATE::COMBO3) isDown = true;
}

void enemyHit::UpdateState()
{
	

	//HIT의 상태가 끝났다.
	if (endFrame())
	{
		if (isDown) _thisEn->SetState(EN_STATE::EN_DOWN);
		else _thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyHit::ExitState()
{
	isDown = false;
}
