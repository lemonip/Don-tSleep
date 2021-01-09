#include "stdafx.h"
#include "bossMove.h"
#include "Boss.h"
#include "Player.h"

void bossMove::EnterState()
{	
	_enterTime = TIME_M->getWorldTime();	 
	_angle = PI / 2;
	_speed = 3.0f;
	_thisBs->ChangeImg("Bs_move");	

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

void bossMove::UpdateState()
{


	if (fabs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getObj()->pos.x) > 50 && fabs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getObj()->pos.z) > 30)
	{		
		_angle = getAngle(_thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z,
			_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		_thisBs->getObj()->pos.x += cosf(_angle) * _speed;
		_thisBs->getObj()->pos.z += -sinf(_angle) * _speed;		
	}	

	else if (fabs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getObj()->pos.x) < 180 && fabs(_thisBs->getPlayerAddress()->getObj().pos.z - _thisBs->getObj()->pos.z) < 50)
	{
		_thisBs->SetState(BS_STATE::WAIT);
	}	
}

void bossMove::ExitState()
{
	
}
