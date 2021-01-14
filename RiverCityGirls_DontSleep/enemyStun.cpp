#include "stdafx.h"
#include "enemyStun.h"
#include "Enemy.h"

void enemyStun::EnterState()
{
	SOUND_M->play("enemy_stun", SFXVOLUME);
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
}

void enemyStun::UpdateState()
{
	EFFECT_M->play("ef_stun", (_thisEn->getRefObj().rc.left + _thisEn->getRefObj().rc.right) / 2, _thisEn->getRefObj().rc.top);
	if(TIME_M->getWorldTime() - _stateTimer > 2.0f)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyStun::ExitState()
{
}
