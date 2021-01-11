#include "stdafx.h"
#include "bossElbowAttack.h"
#include "Boss.h"
#include "Player.h"

void bossElbowAttack::EnterState()
{
	
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_elbow");
	_thisBs->getInfo().isAttack = true;

	LookatPlayer();
	ResetFrame();
}

void bossElbowAttack::UpdateState()
{
	
	

	/*if (_thisBs->getPlayerAddress()->getObj().pos.x > _thisBs->getObj()->pos.x) _thisBs->setDest(DIRECTION::RIGHT);
	else if (_thisBs->getPlayerAddress()->getObj().pos.x < _thisBs->getObj()->pos.x) _thisBs->setDest(DIRECTION::LEFT);
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 8.0f)
	{*/

	if (_thisBs->getInfo().isAttack)
	{
		if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{
			_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x - 50, _thisBs->getObj()->pos.z -150, 200, 100);
		}

		else if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x + 50, _thisBs->getObj()->pos.z -150, 200, 100);
		}
	}
	
}

void bossElbowAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
