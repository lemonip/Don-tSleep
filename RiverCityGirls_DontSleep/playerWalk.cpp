#include "stdafx.h"
#include "playerWalk.h"
#include "Player.h"

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

	//한번더 누르면 대쉬
	if (_thisPl->getInfo().dest == DIRECTION::LEFT && KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->setState(PL_STATE::RUN);

	if (_thisPl->getInfo().dest == DIRECTION::RIGHT && KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->setState(PL_STATE::RUN);

	//키를 누르지 않으면 기본 상태
	if (TIME_M->getWorldTime() - _startTime >0.25f
		&&!KEY_M->isStayKeyDown(VK_LEFT)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& !KEY_M->isStayKeyDown(VK_UP)
		&& !KEY_M->isStayKeyDown(VK_DOWN))
	{
		KEY_M->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}
	

	//이동
	lineMove(_thisPl->getInfo().speed / 2);
	crossMove(_thisPl->getInfo().speed);
}

void playerWalk::ExitState()
{
}
