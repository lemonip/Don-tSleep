#include "stdafx.h"
#include "enemyAttack1.h"
#include "Enemy.h"

void enemyAttack1::EnterState()
{
	_thisEn->SetImage();
}

void enemyAttack1::UpdateState()
{
	LookAtPlayer();

	//공격 렉트 크기와 위치 설정
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.right, _thisEn->getObj()->rc.top, 100, 200);
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.left-100, _thisEn->getObj()->rc.top, 100, 200);
	}

	_thisEn->getInfo().isAttack = true;

	//ATTACK1의 상태가 끝났다.
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x >= _thisEn->getObj()->img->getMaxFrameX())
	{
		//가까우면 때린다.
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
			_thisEn->SetState(EN_STATE::EN_ATTACK2);
		else _thisEn->SetState(EN_STATE::EN_IDLE);

	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x <= 0)
	{
		//가까우면 때린다.
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
			_thisEn->SetState(EN_STATE::EN_ATTACK2);
		else _thisEn->SetState(EN_STATE::EN_IDLE);
	}

}

void enemyAttack1::ExitState()
{
	_thisEn->getInfo().isAttack = false;
}
