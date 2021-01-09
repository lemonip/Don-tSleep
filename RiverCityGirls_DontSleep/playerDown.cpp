#include "stdafx.h"
#include "playerDown.h"

void playerDown::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_down", false);
}

void playerDown::UpdateState()
{
	if (isEndFrame(false) && !_thisPl->getInfo().isDead)_thisPl->setState(PL_STATE::STAND);
	if (isEndFrame(false) && _thisPl->getInfo().isDead)_thisPl->setState(PL_STATE::DEAD);
}

void playerDown::ExitState()
{
}
