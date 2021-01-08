#include "stdafx.h"
#include "bossPhase2.h"
#include "Boss.h"
#include "Player.h"

void bossPhase2::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_phase");
}

void bossPhase2::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 8.0f)
	{
		return;	// 저 시간동안 이미지만 보여주겠다...(?)
	}
}

void bossPhase2::ExitState()
{
}
