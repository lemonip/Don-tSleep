#include "stdafx.h"
#include "playerThrow.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerThrow::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_wBatThrow", false);
	_isCollsion = false;
	
	
}

void playerThrow::UpdateState()
{
	//공격 판정
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (!_isCollsion
			&&_thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj(), 30)
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackInfo._obj.rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{

			if (!_thisPl->getInfo().isAttack)
			{
				_thisPl->SetIsAttack(true);
				_isCollsion = true;
			}
		}
	}
	if (isEndFrame(false))
	{
		//무기타입을 없음으로 변경
		//if (_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)_thisPl->setWeaponType(WEAPON_TYPE::NONE);

		//키조작 가능한 상태로 변경
		_thisPl->setIsControl(true);

		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerThrow::ExitState()
{
}
