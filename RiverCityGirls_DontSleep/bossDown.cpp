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

	EFFECT_M->play("Bss_stun", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
		(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
	
}

void bossDown::ExitState()
{
	_thisBs->SetState(BS_STATE::STANDATTACK);
}
