#include "stdafx.h"
#include "playerSAttackDown.h"

void playerSAttackDown::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_sAttackDown", true);	

	//키입력 막음
	_thisPl->setIsControl(false);

	//무기타입을 없음으로 변경
	dropWeapon();

}

void playerSAttackDown::UpdateState()
{
	//공격여부 체크
	checkEnemy();

	if (isEndFrame(true))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttackDown::ExitState()
{
}
