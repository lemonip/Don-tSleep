#include "stdafx.h"
#include "bossBlock.h"
#include "Boss.h"

void bossBlock::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_block");
	SOUND_M->play("bblock");
	_thisBs->getInfo().isAttack = true;
	LookatPlayer();
	ResetFrame();
}

void bossBlock::UpdateState()
{
}

void bossBlock::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
	
}
