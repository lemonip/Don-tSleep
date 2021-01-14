#include "stdafx.h"
#include "bossGroggy.h"
#include "Boss.h"

void bossGroggy::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_groggy");

	LookatPlayer();
	ResetFrame();
}

void bossGroggy::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 3.5f)
	{
		_thisBs->SetState(BS_STATE::IDLE);
	}

	EFFECT_M->play("Bss_stun", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 250);
}

void bossGroggy::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}