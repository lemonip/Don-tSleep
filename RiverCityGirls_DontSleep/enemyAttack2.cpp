#include "stdafx.h"
#include "enemyAttack2.h"
#include "Enemy.h"

void enemyAttack2::EnterState()
{
	_thisEn->SetImage();
}

void enemyAttack2::UpdateState()
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
	if (_thisEn->getdest() == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x >= _thisEn->getObj()->img->getMaxFrameX())
	{
		_thisEn->SetState(EN_STATE::EN_ATTACK3);
	}
	else if (_thisEn->getdest() == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x <= 0)
	{
		_thisEn->SetState(EN_STATE::EN_ATTACK3);
	}
	
}

void enemyAttack2::ExitState()
{
}
