#include "stdafx.h"
#include "bossElbowAttack.h"
#include "Boss.h"
#include "Player.h"

void bossElbowAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_elbow");
}

void bossElbowAttack::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getobj().pos.x > _thisBs->getPlayerAddress()->getObj().pos.x)
	{
		_thisBs->getinfo().attackRC = RectMakeCenter(_thisBs->getobj().pos.x - 10, _thisBs->getobj().pos.z, 20, 20);
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) 충돌처리 필요, 플레이어 렉트? 
	}

	else if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getobj().pos.x < _thisBs->getPlayerAddress()->getObj().pos.x)
	{
		_thisBs->getinfo().attackRC = RectMakeCenter(_thisBs->getobj().pos.x - 10, _thisBs->getobj().pos.z, 20, 20);
		RECT _temp;
	}
}

void bossElbowAttack::ExitState()
{
	return;
	_thisBs->SetState(BS_STATE::IDLE);
}
