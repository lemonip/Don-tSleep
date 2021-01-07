#include "stdafx.h"
#include "bossDown.h"
#include "Boss.h"

void bossDown::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_down");
}

void bossDown::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 8.0f)
	{
		return;	// 저 시간동안 아무것도 안하겠다...(?)
	}
}

void bossDown::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}
