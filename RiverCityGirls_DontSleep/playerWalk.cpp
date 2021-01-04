#include "stdafx.h"
#include "playerWalk.h"
#include "player.h"

void playerWalk::EnterState()
{
	_thisPl->ChangeImg("pl_walk");
	_startTime = TIME_M->getWorldTime();
	//방향변경가능상태로 전환
	_thisPl->setIsConDest(true);
}

void playerWalk::UpdateState()
{
	_thisPl->ChangeImg("pl_walk");
	/*
	//한번더 누르면 대쉬
	if (_thisPl->GetInfo().dest == PL_DEST::LEFT &&
		KEYMANAGER->isOnceKeyDownV(VK_LEFT))_thisPl->setState(PL_STATE::RUN);

	if (_thisPl->GetInfo().dest == PL_DEST::RIGHT &&
		KEYMANAGER->isOnceKeyDownV(VK_RIGHT))_thisPl->setState(PL_STATE::RUN);

	//키를 누르지 않으면 기본 상태
	
	if (TIME_M->getWorldTime() - _startTime >0.25f
		&&!KEYMANAGER->isStayKeyDown(VK_LEFT)
		&& !KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&& !KEYMANAGER->isStayKeyDown(VK_UP)
		&& !KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		KEYMANAGER->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}
	


	//이동
	lineMove(_thisPl->GetInfo().speed / 2);
	crossMove(_thisPl->GetInfo().speed);*/
}

void playerWalk::ExitState()
{
}
