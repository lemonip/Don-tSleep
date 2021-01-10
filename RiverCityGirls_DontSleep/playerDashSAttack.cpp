#include "stdafx.h"
#include "playerDashSAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerDashSAttack::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_dashSAttack", false);
	//키조작 불가
	_thisPl->setIsControl(false);

	_isCollision = false;
}

void playerDashSAttack::UpdateState()
{
	RECT _temp;
	//공격 판정
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (!_isCollision
			&&_thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj(),30)
			&&IntersectRect(&_temp, &_thisPl->getInfo().attackObj->rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{

			if (!_thisPl->getInfo().isAttack)
			{
				_thisPl->getInfo().isAttack = true;
				_isCollision = true;
			}
		}
	}

	//무기를 떨어뜨림.
	dropWeapon();

	//프레임이 다 돌면 원래 상태로 돌아가기
	if (isEndFrame(false)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	if (isEndFrame(false)
		&& !KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
	
	//달리는 키를 누르고 있으면 달리는 상태로 돌아가기
	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

	//이동
	if (_thisPl->getInfo().dest == DIRECTION::LEFT
		&&_thisPl->getObj().img->getFrameX() <= _thisPl->getObj().img->getMaxFrameX()-10)
		_thisPl->movePos(-_thisPl->getInfo().speed*1.7, 0, 0);

	if (_thisPl->getInfo().dest == DIRECTION::RIGHT
		&&_thisPl->getObj().img->getFrameX() >= 10)
		_thisPl->movePos(_thisPl->getInfo().speed*1.7, 0, 0);


}

void playerDashSAttack::ExitState()
{
	
}
