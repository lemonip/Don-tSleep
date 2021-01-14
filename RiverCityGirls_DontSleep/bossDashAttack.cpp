#include "stdafx.h"
#include "bossDashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossDashAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_speed = 0;
	_thisBs->ChangeImg("Bs_dash2");
	_thisBs->getInfo().isAttack = true;
	
	LookatPlayer();
	ResetFrame();

	_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
		_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);

	_startPos = _thisBs->getObj()->pos;
}

void bossDashAttack::UpdateState()
{

	_speed = 5.0f;

	_thisBs->xzyMove(cosf(_angle) * _speed, -sinf(_angle) * _speed, 0);	

	if (_thisBs->getInfo().isAttack)
	{
		if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->getInfo().rcAttack = RectMake(_thisBs->getObj()->pos.x + 80, _thisBs->getObj()->pos.z - 200, 100, 200);
		}
		else if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{
			_thisBs->getInfo().rcAttack = RectMake(_thisBs->getObj()->pos.x - 80, _thisBs->getObj()->pos.z - 200, 100, 200);
		}		
	}
	
	if (getDistance(_startPos.x, _startPos.z, _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z) > 500)
	{
		if (_thisBs->getInfo().dest == DIRECTION::LEFT && _thisBs->getObj()->imgIndex.x <= 0)
		{
			_thisBs->SetState(BS_STATE::IDLE);
		}
		else if (_thisBs->getInfo().dest == DIRECTION::RIGHT && _thisBs->getObj()->imgIndex.x >= 9)
		{
			_thisBs->SetState(BS_STATE::IDLE);
		}
	}
	else
	{
		if (_thisBs->getInfo().dest == DIRECTION::LEFT && _thisBs->getObj()->imgIndex.x <= 2)
		{
			_thisBs->getObj()->imgIndex = PointMake(9, 0);
		}
		else if (_thisBs->getInfo().dest == DIRECTION::RIGHT && _thisBs->getObj()->imgIndex.x >= 7)
		{
			_thisBs->getObj()->imgIndex = PointMake(0, 1);
		}
	}
	EFFECT_M->play("Bss_dash", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
		(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
}

void bossDashAttack::ExitState()
{
	//_thisBs->SetState(BS_STATE::HOWLING);
	_thisBs->getInfo().isAttack = false;
}
