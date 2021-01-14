#include "stdafx.h"
#include "bossDown.h"
#include "Boss.h"

void bossDown::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_groggy");
	_isEffect = false;

	LookatPlayer();
	ResetFrame();
}

void bossDown::UpdateState()
{

	if (!_isEffect)
	{
		EFFECT_M->play("Bss_stun", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 250);
		//_isEffect = true;
	}

	//EFFECT_M->getIsrunning("Bss_stun");

	if (TIME_M->getWorldTime() - _enterTime > 2.5f)
	{
		_thisBs->SetState(BS_STATE::STANDATTACK);
	}	
}

void bossDown::ExitState()
{
	_thisBs->SetState(BS_STATE::STANDATTACK);
	_thisBs->getInfo().isAttack = false;
	_isEffect = true;
}
