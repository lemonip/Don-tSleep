#include "stdafx.h"
#include "bossBlock.h"
#include "Boss.h"

void bossBlock::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_block");

	LookatPlayer();
	ResetFrame();
}

void bossBlock::UpdateState()
{
	_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 160, 280, 330);
}

void bossBlock::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
	
}
