#include "stdafx.h"
#include "playerPick.h"

void playerPick::EnterState()
{
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
