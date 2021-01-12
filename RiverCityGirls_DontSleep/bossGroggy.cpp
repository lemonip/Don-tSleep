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
	EFFECT_M->play("Bss_stun", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
		(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
}

void bossGroggy::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}