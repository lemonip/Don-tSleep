#include "stdafx.h"
#include "bossIdle.h"
#include "Boss.h"
#include "Player.h"

void bossIdle::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_idle");
}

void bossIdle::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("Bs_idle");


		if (_thisBs->getPlayerAddress()->getObj().pos.x >= _thisBs->getObj()->pos.x)
		{
			_thisBs->getIsMove();
		}
		else
		{
			_thisBs->getIsMove();
		}
	}
}

void bossIdle::ExitState()
{
}
