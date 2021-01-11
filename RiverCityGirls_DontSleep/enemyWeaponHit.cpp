#include "stdafx.h"
#include "enemyWeaponHit.h"
#include "Enemy.h"

void enemyWeaponHit::EnterState()
{
	_thisEn->SetImage();
}

void enemyWeaponHit::UpdateState()
{
	//HIT의 상태가 끝났다.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyWeaponHit::ExitState()
{
}
