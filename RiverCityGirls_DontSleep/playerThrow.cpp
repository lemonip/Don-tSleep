#include "stdafx.h"
#include "playerThrow.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerThrow::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_wBatThrow", false);

	//던짐 트리거 설정
	_thisPl->getInfo().isThrow = true;

	_isCollision = false;

	_thisPl->getInfo().attackObj->pos.x = _thisPl->getObj().pos.x;
	_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y;
	_thisPl->getInfo().attackObj->pos.z = _thisPl->getObj().pos.z;

	_thisPl->getInfo().attackObj->isRender = true;
}

void playerThrow::UpdateState()
{
	//공격 렉트를 어택 오브젝트의 위치에 맞춤.
	_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getInfo().attackObj->pos.x,
		_thisPl->getInfo().attackObj->pos.z + _thisPl->getInfo().attackObj->pos.y,
		_thisPl->getInfo().attackObj->size.x + 200, _thisPl->getInfo().attackObj->size.z + 100);

	RECT _temp;
	//공격 판정
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (!_isCollision
			&&_thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj(), 30)
			&& IntersectRect(&_temp, &_thisPl->getInfo().attackObj->rc,
				&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{

			if (!_thisPl->getInfo().isAttack)
			{
				_thisPl->getInfo().isAttack = true;
				_isCollision = true;
			}
		}
	}
	if (isEndFrame(false))
	{
		//무기참조잃어버림
		//dropWeapon();

		//키조작 가능한 상태로 변경
		_thisPl->setIsControl(true);

		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerThrow::ExitState()
{
}
