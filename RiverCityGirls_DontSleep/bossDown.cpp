#include "stdafx.h"
#include "bossDown.h"
#include "Boss.h"

void bossDown::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_groggy");

	LookatPlayer();
	ResetFrame();
}

void bossDown::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 2.5f)
	{
		_thisBs->SetState(BS_STATE::STANDATTACK);
	}

	EFFECT_M->play("Bss_stun", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 250);
	
}

void bossDown::ExitState()
{
	_thisBs->SetState(BS_STATE::STANDATTACK);
}
