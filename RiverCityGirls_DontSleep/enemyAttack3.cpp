#include "stdafx.h"
#include "enemyAttack3.h"
#include "Enemy.h"

void enemyAttack3::EnterState()
{
	_thisEn->SetImage();
}

void enemyAttack3::UpdateState()
{
	
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::RIGHT);
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::LEFT);
	if (_thisEn->getdest() == DIRECTION::RIGHT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.right, _thisEn->getObj()->rc.top, 50, 50);
	}
	else if (_thisEn->getdest() == DIRECTION::LEFT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.left, _thisEn->getObj()->rc.top, -50, 50);
	}
}

void enemyAttack3::ExitState()
{
}
