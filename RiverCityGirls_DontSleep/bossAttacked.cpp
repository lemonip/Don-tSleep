#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	_thisBs->ChangeImg("attacked");
}

void bossAttacked::UpdateState()
{
	_thisBs->ChangeImg("attacked");
}

void bossAttacked::ExitState()
{
}
