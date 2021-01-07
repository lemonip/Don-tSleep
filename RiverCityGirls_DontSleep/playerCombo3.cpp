#include "stdafx.h"
#include "playerCombo3.h"

void playerCombo3::EnterState()
{
	_thisPl->changeImg("pl_comboAttack3", false);
}

void playerCombo3::UpdateState()
{
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);

	//기본 동작
	basePattern();
}

void playerCombo3::ExitState()
{
}
