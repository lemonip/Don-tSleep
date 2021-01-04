#include "stdafx.h"
#include "bossIdle.h"
#include "Boss.h"

void bossIdle::EnterState()
{
	_thisBs->ChangeImg("idle");
}

void bossIdle::UpdateState()
{
	_thisBs->ChangeImg("idle");
}

void bossIdle::ExitState()
{
}
