#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	LookatPlayer();
	
	switch (RND->getInt(3))
	{		
		
	case 0:
		if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{
			
			_thisBs->ChangeImg("Bs_attacked1");
		}


		if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->ChangeImg("Bs_attacked1");
		}
		break;

	case 1:
		if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{
			_thisBs->ChangeImg("Bs_attacked2");
		}

		if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->ChangeImg("Bs_attacked2");
		}
		break;

	case 2:
		if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{
			_thisBs->ChangeImg("Bs_attacked3");
		}
		if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->ChangeImg("Bs_attacked3");
		}
		break;
	}
	
	ResetFrame();
}

void bossAttacked::UpdateState()
{		

}

void bossAttacked::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
