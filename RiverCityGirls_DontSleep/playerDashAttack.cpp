#include "stdafx.h"
#include "playerDashAttack.h"
#include "player.h"

void playerDashAttack::EnterState()
{
	//방향전환 불가
	_thisPl->setIsConDest(false);
	
	tempTime = TIME_M->getWorldTime();
	_thisPl->ChangeImg("pl_dashAttack");

}

void playerDashAttack::UpdateState()
{
	_thisPl->ChangeImg("pl_dashAttack");
	//임시타이머..원래는 프레임렌더 다돌아가면 변경할듯!
	if (TIME_M->getWorldTime() - tempTime > .5f)_thisPl->setState(PL_STATE::IDLE);

	/*
	//달리는 키를 누르고 있으면 달리는 상태로 돌아가기
	if (TIME_M->getWorldTime() - tempTime > .5f
		&& KEYMANAGER->isStayKeyDown(VK_RIGHT)
		&&_thisPl->GetInfo().indexDest == PL_INDEX_DEST::RIGHT)_thisPl->SetState(PL_STATE::RUN);

	if (TIMEMANAGER->getWorldTime() - tempTime > .5f
		&& KEYMANAGER->isStayKeyDown(VK_LEFT)
		&&_thisPl->GetInfo().indexDest == PL_INDEX_DEST::LEFT)_thisPl->SetState(PL_STATE::RUN);
		
	//이동
	lineMove(_thisPl->GetInfo().speed / 1.5);
	crossMove(_thisPl->GetInfo().speed*1.5);
	*/
}

void playerDashAttack::ExitState()
{
}
