#include "stdafx.h"
#include "playerClimb.h"

void playerClimb::EnterState()
{
	_thisPl->changeImg("pl_climb", false);
	_thisPl->getInfo()._ani->setDefPlayFrame(false, true);
	_thisPl->getInfo()._ani->setFPS(1);
	
}

void playerClimb::UpdateState()
{
	//키입력중일때만.
	_thisPl->getInfo()._ani->start();
	//_thisPl->getInfo()._ani->pause();
}

void playerClimb::ExitState()
{
	_thisPl->getInfo()._ani->stop();
}
