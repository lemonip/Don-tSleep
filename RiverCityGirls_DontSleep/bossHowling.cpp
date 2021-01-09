#include "stdafx.h"
#include "bossHowling.h"
#include "Boss.h"
#include "Player.h"

void bossHowling::EnterState()
{	
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_howling");

	if (_thisBs->getdest() == DIRECTION::RIGHT)
	{
		_thisBs->getObj()->imgIndex.x = 0;
		_thisBs->getObj()->imgIndex.y = 1;
	}

	else if (_thisBs->getdest() == DIRECTION::LEFT)
	{
		_thisBs->getObj()->imgIndex.x = _thisBs->getObj()->img->getMaxFrameX();
		_thisBs->getObj()->imgIndex.y = 0;
	}
}

void bossHowling::UpdateState()
{
	if (_thisBs->getInfo().isAttack)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z, 200, 200);
	}

	if (TIME_M->getWorldTime() - _enterTime > 5.0f)
	{
		_thisBs->SetState(BS_STATE::IDLE);
	}	
}

void bossHowling::ExitState()
{
	_thisBs->getInfo().isAttack = false;
}
