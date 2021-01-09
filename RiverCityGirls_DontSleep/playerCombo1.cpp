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
	_isCollision = false;

	//공격여부
	checkAttack();

}

void playerCombo1::UpdateState()
{
	_thisPl->SetIsAttack(false);


	if (isEndFrame(false) && _thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)
		_thisPl->setState(PL_STATE::IDLE);

	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		//허공에 공격할 경우 프레임이 돌면 기본상태로 돌아간다.
		if (isEndFrame(false)
			&& !IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
			_thisPl->setState(PL_STATE::IDLE);

	//몹한테 첫충돌시
	
	if (!_isCollision
		&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
	{
		_isCollision = true;
		KEY_M->clearVKey();
	}
	

	//몹한테 공격할 경우
	
	if (isEndFrame(false)
		&& KEY_M->getVKeyBuffer().size() != 0
		&& KEY_M->getKeyBuffer(0) == 'S'
		&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
		&& _thisPl->getInfo().weaponType == WEAPON_TYPE::NONE)
	{
		EFFECT_M->play("ef_attack", 10, 10);
			//_thisPl->getInfo().attackInfo._obj.pos.x, _thisPl->getInfo().attackInfo._obj.pos.y);
		_thisPl->setState(PL_STATE::COMBO2);
	}
	
	//시간안에 몹한테 공격 못할 경우
	if (isEndFrame(false)
		&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc, &(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
		&& ((KEY_M->getVKeyBuffer().size() != 0
			&& KEY_M->getKeyBuffer(0) != 'S') || KEY_M->getVKeyBuffer().size() == 0)
		)
		_thisPl->setState(PL_STATE::IDLE);
	}

	//기본 동작
	basePattern();
}

void playerCombo1::ExitState()
{
}
