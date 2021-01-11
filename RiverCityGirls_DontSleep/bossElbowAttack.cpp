#include "stdafx.h"
#include "bossElbowAttack.h"
#include "Boss.h"
#include "Player.h"

void bossElbowAttack::EnterState()
{
	
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_elbow");
	if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getObj()->imgIndex.x = 0;
		_thisBs->getObj()->imgIndex.y = 1;
	}

	else if (_thisBs->getInfo().dest == DIRECTION::LEFT)
	{
		_thisBs->getObj()->imgIndex.x = _thisBs->getObj()->img->getMaxFrameX();
		_thisBs->getObj()->imgIndex.y = 0;
	}
}

void bossElbowAttack::UpdateState()
{
	

	/*if (_thisBs->getPlayerAddress()->getObj().pos.x > _thisBs->getObj()->pos.x) _thisBs->setDest(DIRECTION::RIGHT);
	else if (_thisBs->getPlayerAddress()->getObj().pos.x < _thisBs->getObj()->pos.x) _thisBs->setDest(DIRECTION::LEFT);
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 8.0f)
	{*/

	
		if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{
			_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x - 50, _thisBs->getObj()->pos.z, 200,100);
		}

		else if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x + 50, _thisBs->getObj()->pos.z, 200, 100);
		}
	
}

void bossElbowAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
