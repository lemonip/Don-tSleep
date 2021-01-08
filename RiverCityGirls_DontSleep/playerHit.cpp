#include "stdafx.h"
#include "playerHit.h"


void playerHit::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_hit", false);
}

void playerHit::UpdateState()
{
}

void playerHit::ExitState()
{
}
