#include "stdafx.h"
#include "playerCombo3.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo3::EnterState()
{
	_thisPl->changeImg("pl_comboAttack3", false);
}

void playerCombo3::UpdateState()
{
	//¸÷ÇÑÅ× Ã¹Ãæµ¹½Ã
	if (!_thisPl->getInfo().isAttack
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc)))
	{
		_thisPl->SetIsAttack(true);
	}

	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);

	//°È±â
	walkPattern();
}

void playerCombo3::ExitState()
{
}
