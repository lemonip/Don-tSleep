#include "stdafx.h"
#include "enemyRunAttack.h"
#include "Enemy.h"

void enemyRunAttack::EnterState()
{
	_thisEn->SetImage();
}

void enemyRunAttack::UpdateState()
{
	
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->getInfo().dest = DIRECTION::RIGHT;
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->getInfo().dest = DIRECTION::LEFT;
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.right, _thisEn->getObj()->rc.top, 100, 200);
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.left - 100, _thisEn->getObj()->rc.top, 100, 200);
	}
	

}

void enemyRunAttack::ExitState()
{
}
