#include "stdafx.h"
#include "enemyPatrol.h"


void enemyPatrol::EnterState()
{

}

void enemyPatrol::UpdateState()
{
	//getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 200
	if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 150)
	{
		_thisEn->SetState(EN_STATE::EN_WALK);
	}
	else
	{
		switch (RND->getInt(2))
		{
		case 0:
			_thisEn->SetState(EN_STATE::EN_WALK);
			break;
		case 1:
			_thisEn->SetState(EN_STATE::EN_RUN);
			break;
		}
	}
}

void enemyPatrol::ExitState()
{
}
