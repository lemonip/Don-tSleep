#include "stdafx.h"
#include "bossBlock.h"
#include "Boss.h"

void bossBlock::EnterState()
{
	_thisBs->ChangeImg("Bs_block");
}

void bossBlock::UpdateState()
{
	_thisBs->ChangeImg("Bs_block");
}

void bossBlock::ExitState()
{
}
