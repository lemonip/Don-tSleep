#include "stdafx.h"
#include "playerStun.h"

void playerStun::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_stun", true);
	//키조작불가
	_thisPl->setIsControl(false);

	_stateTimer = TIME_M->getWorldTime();
}

void playerStun::UpdateState()
{
	if (TIME_M->getWorldTime()- _stateTimer >1.5f)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerStun::ExitState()
{
}
