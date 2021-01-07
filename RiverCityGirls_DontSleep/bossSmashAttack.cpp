#include "stdafx.h"
#include "bossSmashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSmashAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_smash");
}

void bossSmashAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		if (_thisBs->getobj().pos.x >= _thisBs->getPlayerAddress()->getObj().pos.x
			&& _thisBs->getIsPhase())
		{
			_thisBs->SetDest(BS_DEST::LEFT);
			_thisBs->SetState(BS_STATE::SMASH);
			_thisBs->ChangeImg("Bs_smash");
			_thisBs->getIsAttack();
		}

		else if (_thisBs->getobj().pos.x <= _thisBs->getPlayerAddress()->getObj().pos.x
			&& _thisBs->getIsPhase())
		{
			_thisBs->SetDest(BS_DEST::RIGHT);
			_thisBs->SetState(BS_STATE::SMASH);
			_thisBs->ChangeImg("Bs_smash");
			_thisBs->getIsAttack();
		}

		else
		{
			!_thisBs->getIsAttack();
		}


	}
}

void bossSmashAttack::ExitState()
{
}
