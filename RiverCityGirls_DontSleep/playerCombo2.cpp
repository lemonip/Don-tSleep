#include "stdafx.h"
#include "playerCombo2.h"

void playerCombo2::EnterState()
{
	_thisPl->changeImg("pl_comboAttack2", false);
	//방향조작 못하는 상태로 변경
	_thisPl->setIsConDest(false);
}

void playerCombo2::UpdateState()
{
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);

	//공격키 누르면 2콤보 + ★몬스터와 충돌도 있어야할듯
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO3);

	//기본 동작
	basePattern();
}

void playerCombo2::ExitState()
{
}
