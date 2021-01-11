#include "stdafx.h"
#include "playerGrab.h"

void playerGrab::EnterState()
{
	//적이랑 인터섹트렉트하고 / 적이 GRAB상태일경우

	//타이머초기화
	_stateTimer = TIME_M->getWorldTime();
	//이미지변경
	_thisPl->changeImg("pl_grab", false);
	_thisPl->setIsControl(false);
}

void playerGrab::UpdateState()
{
	if (KEY_M->isOnceKeyDownV('Q'))
	{
		_thisPl->changeImg("pl_grab", false);
	}

}

void playerGrab::ExitState()
{
}
