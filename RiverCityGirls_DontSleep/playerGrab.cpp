#include "stdafx.h"
#include "playerGrab.h"
#include "Enemy.h"
#include "EnemyManager.h"

void playerGrab::EnterState()
{
	//적이랑 인터섹트렉트하고 / 적이 GRAB상태일경우

	//타이머초기화
	_stateTimer = TIME_M->getWorldTime();
	//이미지변경
	_thisPl->changeImg("pl_grab", false);
	_thisPl->setIsControl(false);
}

void playerGrab::UpdateState()
{
	RECT temp;
	if (KEY_M->isOnceKeyDownV('Q'))
	{
		_thisPl->setIsControl(true);
		_thisPl->getInfo().hasMember = true;
		_thisPl->setState(PL_STATE::IDLE);

		for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
		{
			if (_thisPl->getEnemyM()->getVEnemy()[i]->getState() == EN_STATE::EN_BEGGING)
			{
				if (IntersectRect(&temp, &_thisPl->getInfo().attackRc,
					&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
					&& _thisPl->isRange(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj()))
				{
					_thisPl->getEnemyM()->getVEnemy()[i]->getInfo().isFriend = true;
				}
			}
		}
	}

}

void playerGrab::ExitState()
{
}
