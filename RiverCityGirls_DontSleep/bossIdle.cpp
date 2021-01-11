#include "stdafx.h"
#include "bossIdle.h"
#include "Boss.h"
#include "Player.h"

void bossIdle::EnterState()
{
	_enterTime = TIME_M->getWorldTime();	
	_thisBs->ChangeImg("Bs_idle");

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

void bossIdle::UpdateState()
{	
	if (TIME_M->getWorldTime() - _enterTime > 2.0f)_thisBs->SetState(BS_STATE::MOVE);
}

void bossIdle::ExitState()
{

}
