#include "stdafx.h"
#include "playerClimb.h"

void playerClimb::EnterState()
{
	_thisPl->changeImg("pl_climb", false);

	_thisPl->getObj().ani->init(_thisPl->getRefObj().img->getWidth(), _thisPl->getRefObj().img->getHeight(),
		_thisPl->getRefObj().img->getFrameWidth(), _thisPl->getRefObj().img->getFrameHeight());
	_thisPl->getObj().ani->setDefPlayFrame(false, true);

	_thisPl->getObj().ani->start();
	
}

void playerClimb::UpdateState()
{
	//키입력중일때만.
	
	switch (_thisPl->getInfo().moveDest)
	{
	case MOVE_DIRECTION::RIGHT:
	case MOVE_DIRECTION::LEFT :
		_thisPl->getObj().ani->pause();
	case MOVE_DIRECTION::UP:
		if (!KEY_M->isStayKeyDown(VK_UP)
			&& _thisPl->getObj().ani->isPlay())_thisPl->getObj().ani->pause();
		if (KEY_M->isStayKeyDown(VK_UP)
			&& !_thisPl->getObj().ani->isPlay())_thisPl->getObj().ani->start();
		break;
	case MOVE_DIRECTION::DOWN:
		if (!KEY_M->isStayKeyDown(VK_DOWN)
			&& _thisPl->getObj().ani->isPlay())_thisPl->getObj().ani->pause();
		if (KEY_M->isStayKeyDown(VK_DOWN)
			&& !_thisPl->getObj().ani->isPlay())_thisPl->getObj().ani->start();
		break;
	}
	//렉트템프로 사다리올라가면 올라가는사다리로 상태변경
	if (KEY_M->isOnceKeyDown('J'))
		_thisPl->setState(PL_STATE::CLIMBTOP);

	//렉트템프로 사다리 내려가면 바로 상태변경
	//_thisPl->setState(PL_STATE::IDLE);
}

void playerClimb::ExitState()
{
}
