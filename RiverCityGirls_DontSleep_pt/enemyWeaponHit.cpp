#include "stdafx.h"
#include "enemyWeaponHit.h"
#include "Enemy.h"

void enemyWeaponHit::EnterState()
{
	SOUND_M->playSFX("enemy_down");
	_thisEn->SetImage();
	Damage(_thisEn->getPlayerAddress()->getInfo().force);
}

void enemyWeaponHit::UpdateState()
{
	//HIT�� ���°� ������.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyWeaponHit::ExitState()
{
}
