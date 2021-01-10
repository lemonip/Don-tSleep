#include "stdafx.h"
#include "playerStomp.h"

void playerStomp::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_stomp", true);

	//무기타입을 없음으로 변경
	dropWeapon();

	//공격여부 체크
	checkEnemy();

}

void playerStomp::UpdateState()
{
	//무기판정끗
	_thisPl->getInfo().isAttack = false;
	if (isEndFrame(true))
	{

		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerStomp::ExitState()
{
}
