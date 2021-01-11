#include "stdafx.h"
#include "enemyAttack3.h"
#include "Enemy.h"

void enemyAttack3::EnterState()
{
	_thisEn->SetImage();
}

void enemyAttack3::UpdateState()
{

	LookAtPlayer();

	//공격 렉트 크기와 위치 설정
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.right, _thisEn->getObj()->rc.top, 100, 200);
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.left - 100, _thisEn->getObj()->rc.top, 100, 200);
	}

	//ATTACK3의 상태가 끝났다.
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x >= _thisEn->getObj()->img->getMaxFrameX())
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);

	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x <= 0)
	{
		_thisEn->SetState(EN_STATE::EN_IDLE);
	}

}

void enemyAttack3::ExitState()
{
}
