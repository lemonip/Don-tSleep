#include "stdafx.h"
#include "enemyHardAttack.h"
#include "Enemy.h"

void enemyHardAttack::EnterState()
{
	_thisEn->SetImage();
}

void enemyHardAttack::UpdateState()
{
	
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::RIGHT);
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->setDest(DIRECTION::LEFT);
	if (_thisEn->getdest() == DIRECTION::RIGHT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.right, _thisEn->getObj()->rc.top, 100, 200);
	}
	else if (_thisEn->getdest() == DIRECTION::LEFT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.left - 100, _thisEn->getObj()->rc.top, 100, 200);
	}

	if (_thisEn->getdest() == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x > _thisEn->getObj()->img->getMaxFrameX())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
	else if (_thisEn->getdest() == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x < 0)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}
	
}

void enemyHardAttack::ExitState()
{
}
