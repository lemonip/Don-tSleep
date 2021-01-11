#include "stdafx.h"
#include "bossWait.h"

void bossWait::EnterState()
{

	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_idle");
	
	ResetFrame();
}

void bossWait::UpdateState()
{
	LookatPlayer();

	if (fabs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getObj()->pos.x) < 100 && fabs(_thisBs->getPlayerAddress()->getObj().pos.z - _thisBs->getObj()->pos.z) < 30
		&& TIME_M->getWorldTime() - _enterTime > 0.7f)
	{		

		switch (RND->getInt(4))
		{
		case 0:
			_thisBs->SetState(BS_STATE::SLAP);
			_thisBs->getInfo().isAttack = true;
			break;
		case 1:
			_thisBs->SetState(BS_STATE::ELBOW);
			_thisBs->getInfo().isAttack = true;
			break;
		case 2:
			_thisBs->SetState(BS_STATE::BLOCK);
			_thisBs->getInfo().isAttack = true;
			break;	
		case 3:
			_thisBs->SetState(BS_STATE::HOWLING);
			_thisBs->getInfo().isAttack = true;
			break;
		}

		if (_thisBs->getIsphase())
		{
			switch (RND->getInt(4))
			{
			case 0:
				_thisBs->SetState(BS_STATE::SMASH);
				_thisBs->getInfo().isAttack = true;
				break;
			case 1:
				_thisBs->SetState(BS_STATE::ELBOW);
				_thisBs->getInfo().isAttack = true;
				break;
			case 2:
				_thisBs->SetState(BS_STATE::BLOCK);
				_thisBs->getInfo().isAttack = true;
				break;
			case 3:
				_thisBs->SetState(BS_STATE::HOWLING);
				_thisBs->getInfo().isAttack = true;
				break;
			}
		}
	}	
	else if (fabs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getObj()->pos.x) > 50 && fabs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 30)
	{
		_thisBs->SetState(BS_STATE::MOVE);
	}
}

void bossWait::ExitState()
{
	
}
