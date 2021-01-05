#include "stdafx.h"
#include "player.h"
#include "playerIdle.h"

void playerIdle::EnterState()
{
	_thisPl->changeImg("pl_idle");
	//타이머를 월드타이머로 맞춰서 초기화
	_stateTimer = TIME_M->getWorldTime();
	
}

void playerIdle::UpdateState()
{
	_thisPl->changeImg("pl_idle");
	//일정시간동안 움직임이 없으면 기다림 상태로 전환
	if (TIME_M->getWorldTime() - _stateTimer > 3.0f)_thisPl->setState(PL_STATE::WAIT);

	//걷기
	if (KEY_M->isStayKeyDown(VK_LEFT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_RIGHT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_UP))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_DOWN))_thisPl->setState(PL_STATE::WALK);
	

	
}

void playerIdle::ExitState()
{
}
