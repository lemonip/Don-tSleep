#include "stdafx.h"
#include "bossIdle.h"
#include "Boss.h"

void bossIdle::EnterState()
{
	_thisBs->ChangeImg("Bs_idle");
}

void bossIdle::UpdateState()
{

	_thisBs->ChangeImg("Bs_idle");


	if (_player->getObj().pos.x >= _thisBs->getObj()->pos.x)
	{
		_thisBs->SetState(BS_STATE::MOVE);
	}
	else
	{
		_thisBs->SetState(BS_STATE::MOVE);
	}
}

void bossIdle::ExitState()
{
}
