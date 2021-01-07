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
}

void bossMove::UpdateState()
{	

	if (abs(_thisBs->getPlayerAddress()->getPObj()->pos.x - _thisBs->getobj().pos.x) > 100 && abs(_thisBs->getPlayerAddress()->getPObj()->pos.z - _thisBs->getobj().pos.z) > 20)
	{		
		_angle = getAngle(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z,
			_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		_thisBs->getObj()->pos.x += cosf(_angle) * _speed;
		_thisBs->getObj()->pos.z += -sinf(_angle) * _speed;		
	}	

	if (abs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getobj().pos.x) < 100 && abs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getobj().pos.z) < 20)
	{
		switch (RND->getInt(4))
		{
		case 0:
			_thisBs->SetState(BS_STATE::SLAP);
			break;
		case 1:
			_thisBs->SetState(BS_STATE::ELBOW);
			break;
		case 2:
			_thisBs->SetState(BS_STATE::METEOR);
			break;
		case 3:
			_thisBs->SetState(BS_STATE::BLOCK);
			break;
		}		
	}
	
	
}

void bossMove::ExitState()
{
}
