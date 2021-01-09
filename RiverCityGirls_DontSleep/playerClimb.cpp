#include "stdafx.h"
#include "playerClimb.h"

void playerClimb::EnterState()
{
	_thisPl->changeImg("pl_climb", false);

	_thisPl->getObj().ani->init(_thisPl->getRefObj().img->getWidth(), _thisPl->getRefObj().img->getHeight(),
		_thisPl->getRefObj().img->getFrameWidth(), _thisPl->getRefObj().img->getFrameHeight());
	_thisPl->getObj().ani->setDefPlayFrame(false, true);

	_thisPl->getObj().ani->start();

	_thisPl->changePos(1555, _thisPl->getObj().pos.z, _thisPl->getObj().pos.y);
	
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

	//위아래 움직임
	lineMove(_thisPl->getInfo().speed);

	//렉트템프로 사다리 내려가면 바로 상태변경
	if (KEY_M->isOnceKeyDown(VK_DOWN)
		&& _thisPl->getObj().pos.z>=930)
		_thisPl->setState(PL_STATE::IDLE);

	//렉트템프로 사다리 위로 올라가면 바로 상태변경
	if (KEY_M->isOnceKeyDown(VK_DOWN)
		&& _thisPl->getObj().pos.z <= 430)
		_thisPl->setState(PL_STATE::CLIMBTOP);



	//_thisPl->setState(PL_STATE::IDLE);
}

void playerClimb::ExitState()
{
}
