#include "stdafx.h"
#include "bossGroggy.h"
#include "Boss.h"

void bossGroggy::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_groggy");
	SOUND_M->play("bgroggy", SFXVOLUME);
	_isEffect = false;
	LookatPlayer();
	ResetFrame();
}

void bossGroggy::UpdateState()
{
	if (!_thisBs->getIsphase())
	{
		if (TIME_M->getWorldTime() - _enterTime > 3.5f)
		{
			_thisBs->SetState(BS_STATE::STANDATTACK);
		}

		if (!_isEffect)
		{
			EFFECT_M->play("Bss_stun", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 250);
		}
	}

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);

		if (TIME_M->getWorldTime() - _enterTime > 3.5f)
		{
			_thisBs->SetState(BS_STATE::STANDATTACK);
		}

		if (!_isEffect)
		{
			EFFECT_M->play("Bss_stun", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 250);
		}
	}
}

void bossGroggy::ExitState()
{
	_thisBs->getInfo().isAttack = false;
	_isEffect = true;
}