#include "stdafx.h"
#include "enemyDie.h"
#include "Enemy.h"

void enemyDie::EnterState()
{
	_thisEn->SetImage();
}

void enemyDie::UpdateState()
{
	if(_thisEn->getObj()->alpha > 5) _thisEn->getObj()->alpha -= 5;
	if (endFrame()) _thisEn->getInfo().isDead = true;
}

void enemyDie::ExitState()
{
}
