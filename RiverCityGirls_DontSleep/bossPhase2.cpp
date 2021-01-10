#include "stdafx.h"
#include "bossPhase2.h"
#include "Boss.h"
#include "Player.h"

void bossPhase2::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_phase");

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

void bossPhase2::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 8.0f)
	{
		return;	// 저 시간동안 이미지만 보여주겠다...(?)
	}
}

void bossPhase2::ExitState()
{
}
