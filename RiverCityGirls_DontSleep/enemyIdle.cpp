#include "stdafx.h"
#include "enemyIdle.h"

void enemyIdle::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
	wait = RND->getInt(2);
}

void enemyIdle::UpdateState()
{
	Jump();

	if ((wait && TIME_M->getWorldTime() - _stateTimer > 2.f) || !wait) //대기를 2초 이상 하면
	{
		//가까우면 공격한다.
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			_thisEn->SetState(EN_STATE::EN_JUMP);
			/*
			switch (RND->getInt(4))
			{
			case 0:
			case 1:
				_thisEn->SetState(EN_STATE::EN_ATTACK1);
				break;
			case 2:
				_thisEn->SetState(EN_STATE::EN_ATTACK3);
				break;
			case 3:
				_thisEn->SetState(EN_STATE::EN_JUMP);
				break;
			}
			*/
		}
		else
		{
			//가깝지 않으면 다가간다.
			if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 200)
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
	}

	
}

void enemyIdle::ExitState()
{
	
}
