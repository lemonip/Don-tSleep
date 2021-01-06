#include "stdafx.h"
#include "bossSlapAttack.h"
#include "Boss.h"

void bossSlapAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("slab");
}

void bossSlapAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("slab");
	}
}

void bossSlapAttack::ExitState()
{
}
