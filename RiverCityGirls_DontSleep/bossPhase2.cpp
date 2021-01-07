#include "stdafx.h"
#include "bossPhase2.h"
#include "Boss.h"
#include "Player.h"

void bossPhase2::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_phase");
}

void bossPhase2::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("Bs_phase");
	}
}

void bossPhase2::ExitState()
{
}
