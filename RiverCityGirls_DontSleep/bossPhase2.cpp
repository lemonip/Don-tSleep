#include "stdafx.h"
#include "bossPhase2.h"
#include "Boss.h"
#include "Player.h"

void bossPhase2::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_phase");

	if (_thisBs->getPlayerAddress()->getObj().pos.x < _thisBs->getObj()->pos.x)
	{
		_thisBs->getInfo().dest = DIRECTION::LEFT;
	}
	else if (_thisBs->getPlayerAddress()->getObj().pos.x > _thisBs->getObj()->pos.x)
	{
		_thisBs->getInfo().dest = DIRECTION::RIGHT;
	}

	if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getObj()->imgIndex.x = 0;
		_thisBs->getObj()->imgIndex.y = 1;
	}

	else if (_thisBs->getInfo().dest == DIRECTION::LEFT)
	{
		_thisBs->getObj()->imgIndex.x = _thisBs->getObj()->img->getMaxFrameX();
		_thisBs->getObj()->imgIndex.y = 0;
	}
}

void bossPhase2::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 3.0f)
	{
		_thisBs->SetState(BS_STATE::WAIT);
	}
}

void bossPhase2::ExitState()
{
	_thisBs->SetState(BS_STATE::WAIT);
}
