#include "stdafx.h"
#include "bossDeath.h"
#include "Boss.h"

void bossDeath::EnterState()
{
	
	_thisBs->ChangeImg("death");
}

void bossDeath::UpdateState()
{
	_thisBs->ChangeImg("death");
}

void bossDeath::ExitState()
{
}
