#include "stdafx.h"
#include "bossGroggy.h"
#include "Boss.h"

void bossGroggy::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("groggy");
}

void bossGroggy::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("groggy");
	}
}

void bossGroggy::ExitState()
{
}
