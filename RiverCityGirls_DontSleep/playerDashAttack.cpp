#include "stdafx.h"
#include "playerDashAttack.h"

void playerDashAttack::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_dashAttack", true);
	//키조작 불가
	_thisPl->setIsControl(false);
	//공격여부
	checkEnemy();
}

void playerDashAttack::UpdateState()
{
	//공격판정 1번
	_thisPl->getInfo().isAttack = false;
	//무기를 떨어뜨림.
	dropWeapon();

	//프레임이 다 돌면 원래 상태로 돌아가기
	if (isEndFrame(true)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	if (isEndFrame(true)
		&& !KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	//달리는 키를 누르고 있으면 달리는 상태로 돌아가기
	if (isEndFrame(true)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

	if (isEndFrame(true)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}
	//이동
	if (_thisPl->getInfo().dest == DIRECTION::LEFT)
		_thisPl->movePos(-_thisPl->getInfo().speed*1.2, 0, 0);

	if (_thisPl->getInfo().dest == DIRECTION::RIGHT)
		_thisPl->movePos(_thisPl->getInfo().speed*1.2, 0, 0);
}

void playerDashAttack::ExitState()
{
}
