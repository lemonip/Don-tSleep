#include "stdafx.h"
#include "playerCombo1.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo1::EnterState()
{
	//타격에 여부초기화
	_isCollision = false;

	//이미지 변경
	if (_thisPl->getInfo().attackObj)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatAttack", false);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}
	}
	else _thisPl->changeImg("pl_comboAttack1", false);

	//방향에 따른 공격 렉트 생성
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x - _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE* 0.2, ATTACKSIZE/2);
		break;
	case DIRECTION::RIGHT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x + _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE*0.2, ATTACKSIZE/2);
		break;
	}

	//공격여부: 에너미가 있는지 확인하고 있으면 isAttack을 true로 바꿈
	if (checkEnemy())
	{
		//때린 상태면 이펙트를 보여줌
		EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
			(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
		//타격에 성공했는지 확인
		_isCollision = true;
	}

	//키 벡터를 지운다.
	KEY_M->clearVKey();
}

void playerCombo1::UpdateState()
{
	RECT _temp;
	
	//공격판정 1번만 되도록
	_thisPl->getInfo().isAttack = false;

	//프레임이 다 돌았다.
	if (isEndFrame(false))
	{
		//그 와중에 S 키를 눌렀었다.
		if (!KEY_M->getVKeyBuffer().empty() && KEY_M->getKeyBuffer(0) == 'S' && !_thisPl->getInfo().attackObj)
		{
			for (int i = 0; i < _thisPl->getEnemyM()->getVEnemy().size(); i++)
			{
				//타격을 맞췄었고, 에너미와 충돌중이다.
				if (_isCollision && IntersectRect(&_temp, &_thisPl->getInfo().attackRc,
					&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
					_thisPl->setState(PL_STATE::COMBO2);

				else _thisPl->setState(PL_STATE::IDLE);

			}
		}
		else _thisPl->setState(PL_STATE::IDLE);
	}

	//================================

	//기본 동작 
	basePattern();
}

void playerCombo1::ExitState()
{
}
