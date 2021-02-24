#include "stdafx.h"
#include "bossBlock.h"
#include "Boss.h"

void bossBlock::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_block");
	SOUND_M->playSFX("bblock");
	LookatPlayer();
	ResetFrame();
}

void bossBlock::UpdateState()
{
	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);
	}
}

void bossBlock::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	
}
