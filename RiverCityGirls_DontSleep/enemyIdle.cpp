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
	
	if (_thisEn->getPlayerAddress()->getObj().pos.y < _thisEn->getObj()->pos.y && !_thisEn->getPlayerAddress()->getInfo().isSky)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			_thisEn->SetState(EN_STATE::EN_JUMP);
		}
	}

	if (TIME_M->getWorldTime() - _stateTimer > 2.f)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			switch (RND->getInt(4))
			{
			case 0:
				_thisEn->SetState(EN_STATE::EN_ATTACK1);
				break;
			case 1:
				_thisEn->SetState(EN_STATE::EN_ATTACK1);
				break;
			case 2:
				_thisEn->SetState(EN_STATE::EN_ATTACK1);
				break;
			case 3:
				_thisEn->SetState(EN_STATE::EN_JUMP);
				break;
			}
		}
		else _thisEn->SetState(EN_STATE::EN_PATROL);
	}

	
}

void enemyIdle::ExitState()
{
	
}
