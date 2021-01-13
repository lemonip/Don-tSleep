#include "stdafx.h"
#include "enemyDie.h"
#include "Enemy.h"
#include "ObjectManager.h"

void enemyDie::EnterState()
{
	_thisEn->SetImage();
	_thisEn->getObjectM()->pushItem(ITEM_TYPE::MONEY, vector3(_thisEn->getObj()->pos.x, 0.0f, _thisEn->getObj()->pos.z));
}

void enemyDie::UpdateState()
{
	if(_thisEn->getObj()->alpha > 5) _thisEn->getObj()->alpha -= 5;
	if (endFrame()) _thisEn->getInfo().isDead = true;
}

void enemyDie::ExitState()
{
}
