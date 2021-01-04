#include "stdafx.h"
#include "bossDashAttack.h"
#include "Boss.h"

void bossDashAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("dash");
}

void bossDashAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("dash");
	}
}

void bossDashAttack::ExitState()
{
}
