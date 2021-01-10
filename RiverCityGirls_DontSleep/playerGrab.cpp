#include "stdafx.h"
#include "playerGrab.h"

void playerGrab::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_grab", false);
}

void playerGrab::UpdateState()
{
}

void playerGrab::ExitState()
{
}
