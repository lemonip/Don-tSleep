#include "stdafx.h"
#include "bossWait.h"

void bossWait::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_idle");
	_thisBs->getInfo().isAttack = false;
	ResetFrame();
}

void bossWait::UpdateState()
{
	LookatPlayer();	
	
	if (fabs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getObj()->pos.x) < 120 && fabs(_thisBs->getPlayerAddress()->getObj().pos.z - _thisBs->getObj()->pos.z) < 30
		&& TIME_M->getWorldTime() - _enterTime > 0.7f)
	{		

		switch (RND->getInt(4))
		{
		case 0:
			_thisBs->SetState(BS_STATE::SLAP);			
			break;
		case 1:
			_thisBs->SetState(BS_STATE::ELBOW);				
			break;
		case 2:
			_thisBs->SetState(BS_STATE::BLOCK);
			break;	
		case 3:
			_thisBs->SetState(BS_STATE::HOWLING);			
			break;
		}

		if (_thisBs->getIsphase())
		{
			switch (RND->getInt(4))
			{
			case 0:
				_thisBs->SetState(BS_STATE::SMASH);				
				break;
			case 1:
				_thisBs->SetState(BS_STATE::ELBOW);				
				break;
			case 2:
				_thisBs->SetState(BS_STATE::BLOCK);				
				break;
			case 3:
				_thisBs->SetState(BS_STATE::HOWLING);				
				break;
			}
		}
	}	
	else if (fabs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getObj()->pos.x) > 30 && fabs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 30)
	{
		_thisBs->SetState(BS_STATE::MOVE);
	}
}

void bossWait::ExitState()
{
	
}
