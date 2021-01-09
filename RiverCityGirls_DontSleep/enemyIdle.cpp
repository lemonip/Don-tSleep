#include "stdafx.h"
#include "enemyIdle.h"



void enemyIdle::EnterState()
{
	
	_thisEn->SetImage();
	
	_stateTimer = TIME_M->getWorldTime();
	
}

void enemyIdle::UpdateState()
{
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::RIGHT);
	else if(_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::LEFT);
	

	if (TIME_M->getWorldTime() - _stateTimer > 5.f)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			_thisEn->SetState(EN_STATE::EN_ATTACK1);
		}
		else _thisEn->SetState(EN_STATE::EN_PATROL);
	}
	/*
	if (TIME_M->getWorldTime() - _stateTimer > 5.f)
	{
		_thisEn->SetState(EN_STATE::EN_WRUN);
	}
	*/
}

void enemyIdle::ExitState()
{
	
}
