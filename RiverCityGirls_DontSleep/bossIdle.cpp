#include "stdafx.h"
#include "bossIdle.h"
#include "Boss.h"

void bossIdle::EnterState()
{
	_thisBs->ChangeImg("Bs_idle");
}

void bossIdle::UpdateState()
{
<<<<<<< HEAD
	_thisBs->ChangeImg("idle");
=======
	_thisBs->ChangeImg("Bs_idle");
>>>>>>> c5860b884f4ae64a690c31b4be3f3ab795b95f7d

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
