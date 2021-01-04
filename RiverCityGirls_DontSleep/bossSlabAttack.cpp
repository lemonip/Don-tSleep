#include "stdafx.h"
#include "bossSlabAttack.h"
#include "Boss.h"

void bossSlabAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("slab");
}

void bossSlabAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("slab");
	}
}

void bossSlabAttack::ExitState()
{
}
