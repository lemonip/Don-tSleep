#include "stdafx.h"
#include "bossDeath.h"
#include "Boss.h"

void bossDeath::EnterState()
{
	
	_thisBs->ChangeImg("Bs_death");
}

void bossDeath::UpdateState()
{
	_thisBs->ChangeImg("Bs_death");
}

void bossDeath::ExitState()
{
}
