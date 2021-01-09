#include "stdafx.h"
#include "playerSAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerSAttack::EnterState()
{
	//무기든 상태면 던지기로 상태변경
	if (_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)
	{
		_thisPl->setState(PL_STATE::THROW);
		return;
	}
	//이미지 변경
	_thisPl->changeImg("pl_sAttack", false);	
	
	//키입력 막음
	_thisPl->setIsControl(false);

	
	//공격여부 체크
	checkAttack();
}

void playerSAttack::UpdateState()
{
	//공격판정 1번
	_thisPl->SetIsAttack(false);

	if (isEndFrame(false))
	{
		//키조작 가능한 상태로 변경
		_thisPl->setIsControl(true);

		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttack::ExitState()
{
}
