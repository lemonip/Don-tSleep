#include "stdafx.h"
#include "bossPhase2.h"
#include "Boss.h"

void bossPhase2::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("phase");
}

void bossPhase2::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("phase");
	}
}

void bossPhase2::ExitState()
{
}
