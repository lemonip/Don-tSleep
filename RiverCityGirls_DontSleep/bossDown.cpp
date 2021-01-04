#include "stdafx.h"
#include "bossDown.h"
#include "Boss.h"

void bossDown::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("down");
}

void bossDown::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("down");
	}
}

void bossDown::ExitState()
{
}
