#include "stdafx.h"
#include "bossElbowAttack.h"
#include "Boss.h"
#include "Player.h"

void bossElbowAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_elbow");
}

void bossElbowAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		if (_thisBs->getobj().pos.x >= _thisBs->getPlayerAddress()->getObj().pos.x
			&& _thisBs->getIsElbow())
		{
			_thisBs->SetDest(BS_DEST::LEFT);
			_thisBs->SetState(BS_STATE::ELBOW);
			_thisBs->ChangeImg("Bs_elbow");
			_thisBs->getIsMeteor();
		}

		else if (_thisBs->getobj().pos.x <= _thisBs->getPlayerAddress()->getObj().pos.x
			&& _thisBs->getIsElbow())
		{
			_thisBs->SetDest(BS_DEST::RIGHT);
			_thisBs->SetState(BS_STATE::ELBOW);
			_thisBs->ChangeImg("Bs_elbow");
			_thisBs->getIsMeteor();
		}
		
	}

	
}

void bossElbowAttack::ExitState()
{
}
