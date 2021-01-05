#include "stdafx.h"
#include "playerCombo3.h"
#include "player.h"

void playerCombo3::EnterState()
{
	_thisPl->changeImg("pl_comboAttack3");
	tempTime = TIME_M->getWorldTime();
	//방향조작 못하는 상태로 변경
	_thisPl->setIsConDest(false);
}

void playerCombo3::UpdateState()
{
	_thisPl->changeImg("pl_comboAttack3");

	//임시타이머..원래는 프레임렌더 다돌아가면 변경할듯!
	if (TIME_M->getWorldTime() - tempTime > .5f)_thisPl->setState(PL_STATE::IDLE);

	//기본 동작
	basePattern();
}

void playerCombo3::ExitState()
{
}
