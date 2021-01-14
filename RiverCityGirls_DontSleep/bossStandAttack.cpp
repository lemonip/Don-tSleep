#include "stdafx.h"
#include "bossStandAttack.h"

void bossStandAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_standat");
	_thisBs->getInfo().isAttack = true;

	LookatPlayer();
	ResetFrame();
}

void bossStandAttack::UpdateState()
{
	if (_thisBs->getInfo().isAttack)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 100, 400, 300);
	}	
	EFFECT_M->play("Bss_stand", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
		(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
}


void bossStandAttack::ExitState()
{
	_thisBs->getInfo().isAttack = false;
	_thisBs->SetState(BS_STATE::IDLE);
}
