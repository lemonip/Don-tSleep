#include "stdafx.h"
#include "playerWait.h"

void playerWait::EnterState()
{
	_thisPl->changeImg("pl_wallet");
}

void playerWait::UpdateState()
{
	_thisPl->changeImg("pl_wallet");

	//업데이트정지 유무
	if (pauseUpdate())return;

	//기본동작
	basePattern();

	//강공격
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::SATTACK);

}

void playerWait::ExitState()
{
}
