#include "stdafx.h"
#include "playerSAttack.h"

void playerSAttack::EnterState()
{
	_thisPl->setIsControl(false);
	_thisPl->changeImg("pl_sAttack");

	tempTime = TIME_M->getWorldTime();
}

void playerSAttack::UpdateState()
{
	//임시타이머..원래는 프레임렌더 다돌아가면 변경할듯!
	if(TIME_M->getWorldTime()-tempTime>.5f)_thisPl->setState(PL_STATE::IDLE);
	
}

void playerSAttack::ExitState()
{
}
