#include "stdafx.h"
#include "playerGuard.h"

void playerGuard::EnterState()
{
	_thisPl->changeImg("pl_guard",true);
	//키조작 불가능 상태로 변경
	_thisPl->setIsControl(false);
}

void playerGuard::UpdateState()
{
	//키를 안 누르면 기본상태
	if (!KEY_M->isStayKeyDown('F'))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerGuard::ExitState()
{
}
