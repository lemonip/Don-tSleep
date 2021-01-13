#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	LookatPlayer();
	RECT _temp;
	_enterTime = TIME_M->getWorldTime();
	
	Damaged(_thisBs->getPlayerAddress()->getInfo().force);
		
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
	
}

void bossAttacked::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	if (_thisBs->getPlayerAddress()->getInfo().state == PL_STATE::DASHSATTACK)
	{
		_thisBs->getInfo().isAttack = false;
	}
	else
	_thisBs->getInfo().isAttack = true;
}
