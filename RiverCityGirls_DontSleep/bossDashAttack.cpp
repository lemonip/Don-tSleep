#include "stdafx.h"
#include "bossDashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossDashAttack::EnterState()
{
	_speed = 0;
	_thisBs->ChangeImg("Bs_dash");

	if (_thisBs->getdest() == DIRECTION::RIGHT)
	{
		_thisBs->getObj()->imgIndex.x = 0;
		_thisBs->getObj()->imgIndex.y = 1;
	}

	else if (_thisBs->getdest() == DIRECTION::LEFT)
	{
		_thisBs->getObj()->imgIndex.x = _thisBs->getObj()->img->getMaxFrameX();
		_thisBs->getObj()->imgIndex.y = 0;
	}
}

void bossDashAttack::UpdateState()
{
	_speed = 8.0f;

	
	if (abs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getObj()->pos.x) > 50 && abs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 20)
	{
		_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
			_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		_thisBs->getObj()->pos.x += cosf(_angle) * _speed;
		_thisBs->getObj()->pos.z += -sinf(_angle) * _speed;
	}
	// 3번 공격 필요		
}

void bossDashAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::HOWLING);
	_thisBs->getInfo().isAttack = true;
}
