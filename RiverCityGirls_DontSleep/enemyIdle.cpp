#include "stdafx.h"
#include "enemyIdle.h"



void enemyIdle::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
}

void enemyIdle::UpdateState()
{
	//플레이어가 오른쪽에 있으면 오른쪽 방향을 본다. 반대면 왼쪽을 본다.
	LookAtPlayer();
	
	//플레이어가 나보다 높이 있고 공중이 아니면 점프를 한다
	Jump();
	//대기를 2초 이상 하면
	if (TIME_M->getWorldTime() - _stateTimer > 2.f)
	{
		//가까우면
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
