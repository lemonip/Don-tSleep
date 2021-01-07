#include "stdafx.h"
#include "playerCombo2.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo2::EnterState()
{
	_thisPl->changeImg("pl_comboAttack2", false);
}

void playerCombo2::UpdateState()
{
	//몹한테 첫충돌시
	if (!_thisPl->getInfo().isAttack
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc)))
	{
		_thisPl->SetIsAttack(true);
	}

	//공격키입력 받아서 벡터에 저장
	if (KEY_M->isOnceKeyDownV('S'));
	cout << KEY_M->getVKeyBuffer().size() << endl;

	//몹한테 2콤보 공격할 경우
	if (isEndFrame(false)
		&& KEY_M->getVKeyBuffer().size() != 0
		&& KEY_M->getKeyBuffer(0) == 'S'
		&& KEY_M->getKeyBuffer(1) == 'S'
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc))
		&& _thisPl->getInfo().weaponType == WEAPON_TYPE::NONE
		)
		_thisPl->setState(PL_STATE::COMBO3);

	//시간안에 몹한테 공격 못할 경우
	if (isEndFrame(false)
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc, &(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc))
		&& ((KEY_M->getVKeyBuffer().size() != 0
			&& KEY_M->getKeyBuffer(0) != 'S') || KEY_M->getVKeyBuffer().size() == 0)
		)
		_thisPl->setState(PL_STATE::IDLE);

	//걷기
	walkPattern();
	
}

void playerCombo2::ExitState()
{
}
