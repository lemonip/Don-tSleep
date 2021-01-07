#include "stdafx.h"
#include "playerSAttackDown.h"

void playerSAttackDown::EnterState()
{
	_thisPl->changeImg("pl_sAttackDown", true);	
	_thisPl->setIsControl(false);
}

void playerSAttackDown::UpdateState()
{
	if (isEndFrame(true))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttackDown::ExitState()
{
}
