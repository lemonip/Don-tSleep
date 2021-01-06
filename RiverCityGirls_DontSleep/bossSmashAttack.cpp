#include "stdafx.h"
#include "bossSmashAttack.h"
#include "Boss.h"

void bossSmashAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("Bs_smash");
}

void bossSmashAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("Bs_smash");
	}
}

void bossSmashAttack::ExitState()
{
}
