#include "stdafx.h"
#include "playerSAttack.h"
#include "Player.h"

void playerSAttack::EnterState()
{
	_thisPl->setIsControl(false);
	_thisPl->ChangeImg("pl_SAttack");

	tempTime = TIME_M->getWorldTime();
}

void playerSAttack::UpdateState()
{
	_thisPl->ChangeImg("pl_SAttack");

	//임시타이머..원래는 프레임렌더 다돌아가면 변경할듯!
	if(TIME_M->getWorldTime()-tempTime>.5f)_thisPl->setState(PL_STATE::IDLE);
	
}

void playerSAttack::ExitState()
{
}
