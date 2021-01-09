#include "stdafx.h"
#include "playerCombo2.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo2::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_comboAttack2", false);
	_isCollision = false;

	//공격여부
	checkAttack();
}

void playerCombo2::UpdateState()
{
	_thisPl->SetIsAttack(false);
	//공격키입력 받아서 벡터에 저장
	if (KEY_M->isOnceKeyDownV('S'));

	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		//몹한테 첫충돌시
		if (!_isCollision
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{
			_isCollision = true;
		}

		//몹한테 2콤보 공격할 경우
		if (isEndFrame(false)
			&& KEY_M->getVKeyBuffer().size() >= 2
			&& KEY_M->getKeyBuffer(0) == 'S'
			&& KEY_M->getKeyBuffer(1) == 'S'
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
			&& _thisPl->getInfo().weaponType == WEAPON_TYPE::NONE)
			_thisPl->setState(PL_STATE::COMBO3);

		//시간안에 몹한테 공격 못할 경우
		if (isEndFrame(false)
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc, &(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
			&& ((KEY_M->getVKeyBuffer().size() != 0
				&& KEY_M->getKeyBuffer(0) != 'S') || KEY_M->getVKeyBuffer().size() <= 1)
			)
			_thisPl->setState(PL_STATE::IDLE);
	}

	//걷기
	walkPattern();
	
}

void playerCombo2::ExitState()
{
}
