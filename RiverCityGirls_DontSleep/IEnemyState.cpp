#include "stdafx.h"
#include "IEnemyState.h"

void IEnemyState::Jump()
{
	//플래이어가 나보다 높이 있고 공중이 아니면 점프를 한다.
	if (_thisEn->getPlayerAddress()->getObj().pos.y < _thisEn->getObj()->pos.y && !_thisEn->getPlayerAddress()->getInfo().isSky)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			_thisEn->SetState(EN_STATE::EN_JUMP);
		}
	}
}

void IEnemyState::LookAtPlayer()
{
	//플래이어가 오른쪽에 있으면 오른쪽 방향을 본다. 반대면 왼쪽을 본다.
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->getInfo().dest = DIRECTION::RIGHT;
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->getInfo().dest = DIRECTION::LEFT;
}
