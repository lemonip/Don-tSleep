#include "stdafx.h"
#include "bossHowling.h"
#include "Boss.h"

void bossHowling::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_howling");
}

void bossHowling::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("Bs_howling");
	}
}

void bossHowling::ExitState()
{
}
