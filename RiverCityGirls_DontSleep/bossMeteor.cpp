#include "stdafx.h"
#include "bossMeteor.h"
#include "Boss.h"
#include "Player.h"

void bossMeteor::EnterState()
{
	_angle = PI / 2;
	_speed = 25.0f;
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_meteor");
	_thisBs->getInfo().jumpPower = 20.0f;
	_thisBs->getInfo().isSky = false;
	_thisBs->getInfo().gravity = 5.0f;

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

void bossMeteor::UpdateState()
{
	
	
	if (TIME_M->getWorldTime() - _enterTime > 0.5f)
	{
		if (_thisBs->getInfo().isSky)
		{			
			_thisBs->getObj()->pos.y = -400;
			_thisBs->getObj()->pos.y -= _thisBs->getInfo().jumpPower;

			
		}
	}
	if (TIME_M->getWorldTime() - _enterTime > 3.0f)
	{
		_thisBs->getInfo().isSky = false;

		_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
		_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		_thisBs->getObj()->pos.x += cosf(_angle) * _speed;
		_thisBs->getObj()->pos.z += -sinf(_angle) * _speed;
		_thisBs->getObj()->pos.y -= tanf(_angle) * _speed * 3;

		_thisBs->ChangeImg("Bs_meteordown");

		if (_thisBs->getObj()->pos.y > _thisBs->getPlayerAddress()->getPObj()->pos.y)
		{
			_thisBs->getObj()->pos.y = 0;
		}

		if (TIME_M->getWorldTime() - _enterTime > 3.5f)
		{
			_thisBs->SetState(BS_STATE::DOWN);
		}
	}
	
}

void bossMeteor::ExitState()
{
	_thisBs->ChangeImg("Bs_meteor");
	_thisBs->SetState(BS_STATE::DOWN);
}
