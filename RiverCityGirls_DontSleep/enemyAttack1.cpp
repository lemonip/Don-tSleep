#include "stdafx.h"
#include "enemyAttack1.h"
#include "Enemy.h"

void enemyAttack1::EnterState()
{
	_thisEn->SetImage();
	LookAtPlayer();

}

void enemyAttack1::UpdateState()
{

	Attack();


	_thisEn->getInfo().isAttack = true;

	//ATTACK1의 상태가 끝났다.
	if (endFrame())
	{
		//가까우면 때린다.
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
			_thisEn->SetState(EN_STATE::EN_ATTACK2);
		else _thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyAttack1::ExitState()
{
	_thisEn->getInfo().isAttack = false;
}
