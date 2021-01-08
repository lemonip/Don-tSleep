#include "stdafx.h"
#include "bossIdle.h"
#include "Boss.h"
#include "Player.h"

void bossIdle::EnterState()
{
	_enterTime = TIME_M->getWorldTime();	
	_thisBs->ChangeImg("Bs_idle");
}

void bossIdle::UpdateState()
{	
	if (TIME_M->getWorldTime() - _enterTime > 3.0f)_thisBs->SetState(BS_STATE::MOVE);
}

void bossIdle::ExitState()
{
}
