#include "stdafx.h"
#include "playerIdle.h"

void playerIdle::EnterState()
{
	_thisPl->changeImg("pl_idle");
	//키조작 가능한 상태로 변경
	_thisPl->setIsControl(true);
	_thisPl->setIsControl(true);

	//타이머를 월드타이머로 맞춰서 초기화
	_stateTimer = TIME_M->getWorldTime();
	
}

void playerIdle::UpdateState()
{
	_thisPl->changeImg("pl_idle");
	//일정시간동안 움직임이 없으면 기다림 상태로 전환
	if (TIME_M->getWorldTime() - _stateTimer > 3.0f)_thisPl->setState(PL_STATE::WAIT);

	//기본 동작
	basePattern();
	
	//강공격
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::SATTACK);
	
}

void playerIdle::ExitState()
{
}
