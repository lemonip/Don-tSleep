#include "stdafx.h"
#include "playerCombo1.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo1::EnterState()
{
	//이미지 변경
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->changeImg("pl_comboAttack1", false);	break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatAttack", false);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}
}

void playerCombo1::UpdateState()
{
	//허공에 공격할 경우 프레임이 돌면 기본상태로 돌아간다.
	if (isEndFrame(false)
		&& !IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc,
		&(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc)))
		_thisPl->setState(PL_STATE::IDLE);

	if (isEndFrame(false) && _thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)
		_thisPl->setState(PL_STATE::IDLE);

	//몹한테 첫충돌시
	if(!_thisPl->getInfo().isAttack
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc)))
	{
		_thisPl->SetIsAttack(true);
		KEY_M->clearVKey();
	}

	//몹한테 공격할 경우
	if (isEndFrame(false)
		&& KEY_M->getVKeyBuffer().size() !=0
		&& KEY_M->getKeyBuffer(0) == 'S'
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc))
		&& _thisPl->getInfo().weaponType == WEAPON_TYPE::NONE)
	{
		_thisPl->setState(PL_STATE::COMBO2);
		_thisPl->SetIsAttack(false); 
	}
	
	//시간안에 몹한테 공격 못할 경우
	if (isEndFrame(false)
		&& IntersectRect(&temp, &_thisPl->getInfo().attackInfo.rc, &(_thisPl->getEnemyM()->getVEnemy()[0]->getRefObj().rc))
		&&(( KEY_M->getVKeyBuffer().size() != 0
		&& KEY_M->getKeyBuffer(0) != 'S')|| KEY_M->getVKeyBuffer().size() == 0)
		)
		_thisPl->setState(PL_STATE::IDLE);
	

	//기본 동작
	basePattern();
}

void playerCombo1::ExitState()
{
}
