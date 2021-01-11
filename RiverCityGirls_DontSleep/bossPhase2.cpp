#include "stdafx.h"
#include "bossPhase2.h"
#include "Boss.h"
#include "Player.h"

void bossPhase2::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_phase");

	LookatPlayer();
	ResetFrame();
}

void bossPhase2::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 3.0f)
	{
		_thisBs->SetState(BS_STATE::WAIT);
	}
}

void bossPhase2::ExitState()
{
	_thisBs->SetState(BS_STATE::WAIT);
}
