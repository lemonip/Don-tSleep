#include "stdafx.h"
#include "bossStandAttack.h"
#include "Boss.h"
#include "Player.h"

void bossStandAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_standat");
}

void bossStandAttack::UpdateState()
{
	if (_thisBs->getobj().pos.x >= _thisBs->getPlayerAddress()->getObj().pos.x
		&& _thisBs->getIsDown())
	{
		_thisBs->SetDest(BS_DEST::LEFT);
		_thisBs->SetState(BS_STATE::STANDATTACK);
		_thisBs->getIsAttack();
	}

	else if(_thisBs->getobj().pos.x <= _thisBs->getPlayerAddress()->getObj().pos.x
		&& _thisBs->getIsDown())
	{
		_thisBs->SetDest(BS_DEST::RIGHT);
		_thisBs->SetState(BS_STATE::STANDATTACK);
		_thisBs->getIsAttack();
	}

	else
	{
		!_thisBs->getIsAttack();
	}	
}

void bossStandAttack::ExitState()
{
}
