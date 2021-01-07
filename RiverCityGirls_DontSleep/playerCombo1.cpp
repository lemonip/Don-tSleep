#include "stdafx.h"
#include "playerCombo1.h"

void playerCombo1::EnterState()
{
	_thisPl->changeImg("pl_comboAttack1", false);
	tempTime = TIME_M->getWorldTime();
}

void playerCombo1::UpdateState()
{
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);
	//프레임이 끝나면 공격렉트를 만들어서 충돌했는지 확인하고 데미지를 줌! 끝에하면될거같은느낌..

	//공격키 누르면 2콤보 + ★몬스터와 충돌도 있어야할듯
	if(KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO2);

	//기본 동작
	basePattern();
}

void playerCombo1::ExitState()
{
}
