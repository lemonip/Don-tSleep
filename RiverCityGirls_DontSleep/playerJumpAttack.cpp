#include "stdafx.h"
#include "playerJumpAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerJumpAttack::EnterState()
{
	//방향 변경 불가
	_thisPl->setIsConDest(false);

	_thisPl->changeImg("pl_jumpAttack",false);

	//무기타입을 없음으로 변경
	if (_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)_thisPl->setWeaponType(WEAPON_TYPE::NONE);
	_isCollsion = false;
}

void playerJumpAttack::UpdateState()
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

	
	//이동
	crossMove(_thisPl->getInfo().speed*1.2);
	lineMove(_thisPl->getInfo().speed / 2);

}

void playerJumpAttack::ExitState()
{
}
