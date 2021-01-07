#include "stdafx.h"
#include "bossSlapAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSlapAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_slap");
}

void bossSlapAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		if (_thisBs->getobj().pos.x >= _thisBs->getPlayerAddress()->getObj().pos.x
			&& !_thisBs->getIsPhase() && _thisBs->getIsAttack())
		{
			_thisBs->SetDest(BS_DEST::LEFT);
			_thisBs->SetState(BS_STATE::SLAP);
			_thisBs->ChangeImg("Bs_slap");
			_thisBs->getIsAttack();
			_thisBs->getIsElbow();
		}

		else if (_thisBs->getobj().pos.x <= _thisBs->getPlayerAddress()->getObj().pos.x
			&& !_thisBs->getIsPhase() && _thisBs->getIsAttack())
		{
			_thisBs->SetDest(BS_DEST::RIGHT);
			_thisBs->SetState(BS_STATE::SLAP);
			_thisBs->ChangeImg("Bs_slap");
			_thisBs->getIsAttack();
			_thisBs->getIsElbow();
		}
			
		else
		{
			!_thisBs->getIsAttack();
		}

		
	}
}

void bossSlapAttack::ExitState()
{
}
