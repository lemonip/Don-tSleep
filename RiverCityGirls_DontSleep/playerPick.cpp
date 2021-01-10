#include "stdafx.h"
#include "playerPick.h"

void playerPick::EnterState()
{
	if (!checkWeapon()) { _thisPl->setState(PL_STATE::IDLE); return; }

	_thisPl->getInfo().attackObj->isRender = false;

	//이미지변경
	_thisPl->changeImg("pl_pick", false);
}

void playerPick::UpdateState()
{
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);
}

void playerPick::ExitState()
{
}
