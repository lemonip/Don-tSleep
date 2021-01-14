#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	LookatPlayer();
	RECT _temp;
	_enterTime = TIME_M->getWorldTime();
	_thisBs->getInfo().isAttack = true;

	// 이미지를 바꿈
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
	//이미지를 초기화
	ResetFrame();
}

void bossAttacked::UpdateState()
{		

	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);
	}

	if (TIME_M->getWorldTime() - _enterTime > 1.5f)
	{
		_thisBs->SetState(BS_STATE::WAIT);
	}
	/*if (_thisBs->getInfo().hp == _thisBs->getInfo().maxHp / 1.6f)
	{
		_thisBs->SetState(BS_STATE::DOWN);
	}

	else if (_thisBs->getInfo().hp == _thisBs->getInfo().maxHp / 2)
	{
		_thisBs->SetState(BS_STATE::GROGGY);
	}

	else if (_thisBs->getInfo().hp == _thisBs->getInfo().maxHp / 3)
	{
		_thisBs->SetState(BS_STATE::PHASE);
	}*/	
}

void bossAttacked::ExitState()
{
	
}
