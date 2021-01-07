#include "stdafx.h"
#include "playerClimb.h"

void playerClimb::EnterState()
{
	_thisPl->changeImg("pl_climb", false);
	_thisPl->getInfo().ani->setDefPlayFrame(false, true);
	_thisPl->getInfo().ani->setFPS(1);
	
}

void playerClimb::UpdateState()
{
	//키입력중일때만.
	_thisPl->getInfo().ani->start();
	//_thisPl->getInfo()._ani->pause();
}

void playerClimb::ExitState()
{
	_thisPl->getInfo().ani->stop();
}
