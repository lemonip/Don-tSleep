#include "stdafx.h"
#include "playerDead.h"


void playerDead::EnterState()
{
	//무기떨어뜨리기
	dropWeapon();

	//넘어져있었으면 바로 죽음이미지로 변경
	if (_thisPl->getInfo().preState == PL_STATE::DOWN)
	_thisPl->changeImg("pl_dead", false);

	//사망
	_thisPl->getInfo().isDead = true;

	//키조작 불가
	_thisPl->setIsControl(false);
}

void playerDead::UpdateState()
{
	//넘어져있지 않았다면 넘어뜨림
	if (_thisPl->getInfo().preState != PL_STATE::DOWN )
		_thisPl->setState(PL_STATE::DOWN);
}

void playerDead::ExitState()
{
}
