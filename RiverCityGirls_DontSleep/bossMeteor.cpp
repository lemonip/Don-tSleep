#include "stdafx.h"
#include "bossMeteor.h"
#include "Boss.h"
#include "Player.h"

void bossMeteor::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_meteor");
}

void bossMeteor::UpdateState()
{
	if (_count % 8 == 0)
	{
		if (_thisBs->getobj().pos.x >= _thisBs->getPlayerAddress()->getObj().pos.x
			&& !_thisBs->getIsPhase() && _thisBs->getIsMeteor())
		{
			_thisBs->SetDest(BS_DEST::LEFT);
			_thisBs->SetState(BS_STATE::METEOR);
			_thisBs->ChangeImg("Bs_meteor");
			_thisBs->getIsDash();
		}

		else if (_thisBs->getobj().pos.x <= _thisBs->getPlayerAddress()->getObj().pos.x
			&& !_thisBs->getIsPhase() && _thisBs->getIsMeteor())
		{
			_thisBs->SetDest(BS_DEST::RIGHT);
			_thisBs->SetState(BS_STATE::METEOR);
			_thisBs->ChangeImg("Bs_meteor");
			_thisBs->getIsDash();
		}
		
	}
}

void bossMeteor::ExitState()
{
}
