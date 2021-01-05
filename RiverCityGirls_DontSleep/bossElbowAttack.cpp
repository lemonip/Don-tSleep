#include "stdafx.h"
#include "bossElbowAttack.h"
#include "Boss.h"

void bossElbowAttack::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("elbow");
}

void bossElbowAttack::UpdateState()
{
	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("elbow");
	}

	
}

void bossElbowAttack::ExitState()
{
}
