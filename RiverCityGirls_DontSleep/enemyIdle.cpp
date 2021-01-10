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
	
	
	if (TIME_M->getWorldTime() - _stateTimer > 2.f)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 50
			&& _thisEn->getObj()->pos.z >= _thisEn->getPlayerAddress()->getObj().shadow.RT.z && _thisEn->getObj()->pos.z <= _thisEn->getPlayerAddress()->getObj().shadow.RB.z)
		{
			_thisEn->SetState(EN_STATE::EN_ATTACK1);
		}
		else _thisEn->SetState(EN_STATE::EN_PATROL);
	}
	
		
	
	
}

void enemyIdle::ExitState()
{
	
}
