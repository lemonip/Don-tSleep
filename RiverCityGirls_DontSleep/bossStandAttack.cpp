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
}


void bossStandAttack::ExitState()
{
	_thisBs->getInfo().isAttack = false;
	_thisBs->SetState(BS_STATE::IDLE);
}
