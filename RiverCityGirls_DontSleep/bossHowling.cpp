#include "stdafx.h"
#include "bossHowling.h"
#include "Boss.h"
#include "Player.h"

void bossHowling::EnterState()
{	
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_howling");

	_thisBs->getInfo().isAttack = true;
	   
	LookatPlayer();
	ResetFrame();
}

void bossHowling::UpdateState()
{
	

	if (_thisBs->getInfo().isAttack)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150, 300, 300);
	}
	
	if (TIME_M->getWorldTime() - _enterTime > 5.0f)
	{
		_thisBs->SetState(BS_STATE::DASH);
	}	
}

void bossHowling::ExitState()
{
	_thisBs->getInfo().isAttack = false;
	_thisBs->SetState(BS_STATE::DASH);
}
