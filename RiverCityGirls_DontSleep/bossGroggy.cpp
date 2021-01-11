#include "stdafx.h"
#include "bossGroggy.h"
#include "Boss.h"

void bossGroggy::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_groggy");

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

void bossGroggy::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 3.5f)
	{
		_thisBs->SetState(BS_STATE::IDLE);
	}
}

void bossGroggy::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}