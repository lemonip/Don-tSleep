#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	_thisBs->ChangeImg("Bs_attacked");

	LookatPlayer();
	ResetFrame();	
}

void bossAttacked::UpdateState()
{

	
	
}

void bossAttacked::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}
