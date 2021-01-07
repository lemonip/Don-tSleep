#include "stdafx.h"
#include "bossDashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossDashAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_dash");
}

void bossDashAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		if (_thisBs->getobj().pos.x >= _thisBs->getPlayerAddress()->getObj().pos.x
			&& _thisBs->getIsDash())
		{
			_thisBs->SetDest(BS_DEST::LEFT);
			_thisBs->SetState(BS_STATE::DASH);
			_thisBs->ChangeImg("Bs_dash");
			_thisBs->getIsHowling();
		}
		
		else if (_thisBs->getobj().pos.x <= _thisBs->getPlayerAddress()->getObj().pos.x
			&& _thisBs->getIsDash())
		{
			_thisBs->SetDest(BS_DEST::RIGHT);
			_thisBs->SetState(BS_STATE::DASH);
			_thisBs->ChangeImg("Bs_dash");
			_thisBs->getIsHowling();
		}
	
	}
}

void bossDashAttack::ExitState()
{
}
