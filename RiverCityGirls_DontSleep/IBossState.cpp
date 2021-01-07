#include "stdafx.h"
#include "IBossState.h"
#include "Boss.h"

void IBossState::BossMove()
{
	_thisBs->SetState(BS_STATE::MOVE);
}
