#include "stdafx.h"
#include "playerWait.h"

void playerWait::EnterState()
{
	_thisPl->changeImg("pl_wait",false);
}

void playerWait::UpdateState()
{
	//기본동작
	basePattern();

	//강공격
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::SATTACK);

}

void playerWait::ExitState()
{
}
