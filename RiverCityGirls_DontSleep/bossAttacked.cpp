#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	_thisBs->ChangeImg("Bs_attacked");
}

void bossAttacked::UpdateState()
{
		
	_thisBs->ChangeImg("Bs_attacked");
	
}

void bossAttacked::ExitState()
{
}
