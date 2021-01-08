#include "stdafx.h"
#include "bossDashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossDashAttack::EnterState()
{
	_angle = PI / 2;
	_speed = 8.0f;
	_thisBs->ChangeImg("Bs_dash");
}

void bossDashAttack::UpdateState()
{
	if (abs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getobj().pos.x) > 50 && abs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getobj().pos.z) > 20)
	{
		_angle = getAngle(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z,
			_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		_thisBs->getObj()->pos.x += cosf(_angle) * _speed;
		_thisBs->getObj()->pos.z += -sinf(_angle) * _speed;
	}
	// 3번 공격 필요		
}

void bossDashAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::HOWLING);
}
