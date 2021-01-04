#include "stdafx.h"
#include "bossBlock.h"
#include "Boss.h"

void bossBlock::EnterState()
{
	_thisBs->ChangeImg("block");
}

void bossBlock::UpdateState()
{
	_thisBs->ChangeImg("block");
}

void bossBlock::ExitState()
{
}
