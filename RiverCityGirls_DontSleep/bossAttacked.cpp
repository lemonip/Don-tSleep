#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	_thisBs->ChangeImg("Bs_attacked");

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

void bossAttacked::UpdateState()
{
	

	
	
}

void bossAttacked::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}
