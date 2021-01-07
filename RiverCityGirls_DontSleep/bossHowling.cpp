#include "stdafx.h"
#include "bossHowling.h"
#include "Boss.h"
#include "Player.h"

void bossHowling::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_howling");
}

void bossHowling::UpdateState()
{
	if (_count % 8 == 0)
	{
		if (_thisBs->getobj().pos.x >= _thisBs->getPlayerAddress()->getObj().pos.x
			&& _thisBs->getIsHowling())
		{
			_thisBs->SetDest(BS_DEST::LEFT);
			_thisBs->SetState(BS_STATE::HOWLING);
			_thisBs->ChangeImg("Bs_howling");
			_thisBs->getIsMove();
			
		}

		else if (_thisBs->getobj().pos.x <= _thisBs->getPlayerAddress()->getObj().pos.x
			&& _thisBs->getIsHowling())
		{
			_thisBs->SetDest(BS_DEST::RIGHT);
			_thisBs->SetState(BS_STATE::HOWLING);
			_thisBs->ChangeImg("Bs_howling");
			_thisBs->getIsMove();
			
		}
		
	}
}

void bossHowling::ExitState()
{
}
