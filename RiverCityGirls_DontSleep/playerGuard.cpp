#include "stdafx.h"
#include "playerGuard.h"
#include "player.h"

void playerGuard::EnterState()
{
	_thisPl->ChangeImg("pl_guard");
	//키조작 불가능 상태로 변경
	_thisPl->setIsControl(false);
}

void playerGuard::UpdateState()
{
	_thisPl->ChangeImg("pl_guard");

	//키를 안 누르면 기본상태
	if (!KEY_M->isStayKeyDown(VK_SPACE))
	{
		KEY_M->clearVKey();
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerGuard::ExitState()
{
}
