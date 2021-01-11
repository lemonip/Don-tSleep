#include "stdafx.h"
#include "enemyAttack3.h"
#include "Enemy.h"

void enemyAttack3::EnterState()
{
	_thisEn->SetImage();
	LookAtPlayer();
}

void enemyAttack3::UpdateState()
{

	
	Attack();

	//ATTACK3의 상태가 끝났다.
	if (endFrame())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}

}

void enemyAttack3::ExitState()
{
	_thisEn->getInfo().isAttack = false;
}
