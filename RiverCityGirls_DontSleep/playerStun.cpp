#include "stdafx.h"
#include "playerStun.h"

void playerStun::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_stun", true);
	//키조작불가
	_thisPl->setIsControl(false);

	//이팩트 출력
	EFFECT_M->play("ef_stun", (_thisPl->getObj().rc.left + _thisPl->getObj().rc.right) /2, _thisPl->getObj().rc.top);

	//기절 타이머 초기화
	_stateTimer = TIME_M->getWorldTime();
}

void playerStun::UpdateState()
{
	if (TIME_M->getWorldTime()- _stateTimer >1.5f)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerStun::ExitState()
{
}
