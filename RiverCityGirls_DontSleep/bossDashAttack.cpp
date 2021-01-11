#include "stdafx.h"
#include "bossDashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossDashAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_speed = 0;
	_thisBs->ChangeImg("Bs_idle");
	

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

void bossDashAttack::UpdateState()
{
		
	_speed = 4.0f;

	_thisBs->ChangeImg("Bs_dash2");

	_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
		_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
	_thisBs->getObj()->pos.x += cosf(_angle) * _speed;
	_thisBs->getObj()->pos.z += -sinf(_angle) * _speed;
	
	

	/*if (_thisBs->getObj()->imgIndex.x == _thisBs->getObj()->img->getMaxFrameX() && _thisBs->getdest() == DIRECTION::LEFT)
	{
		//_thisBs->getInfo().isAttack = false;
	}

	if (_thisBs->getObj()->imgIndex.x == 0 && _thisBs->getdest() == DIRECTION::RIGHT)
	{
		//_thisBs->getInfo().isAttack = false;
	}
	// 3번 공격 필요		*/
}

void bossDashAttack::ExitState()
{
	//_thisBs->SetState(BS_STATE::HOWLING);
	//_thisBs->getInfo().isAttack = true;
}
