#include "stdafx.h"
#include "bossStandAttack.h"
#include "Boss.h"

void bossStandAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("standat");
}

void bossStandAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("standat");
	}
	
}

void bossStandAttack::ExitState()
{
}
