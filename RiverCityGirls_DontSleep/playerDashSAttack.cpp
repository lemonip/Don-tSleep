#include "stdafx.h"
#include "playerDashSAttack.h"

void playerDashSAttack::EnterState()
{
	//방향전환 불가
	_thisPl->setIsConDest(false);

	tempTime = TIME_M->getWorldTime();
	_thisPl->changeImg("pl_dashSAttack");
}

void playerDashSAttack::UpdateState()
{
	_thisPl->changeImg("pl_dashSAttack");
	//임시타이머..원래는 프레임렌더 다돌아가면 변경할듯!
	if (TIME_M->getWorldTime() - tempTime > .5f)_thisPl->setState(PL_STATE::IDLE);

	//달리는 키를 누르고 있으면 달리는 상태로 돌아가기
	if (TIME_M->getWorldTime() - tempTime > .5f
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)_thisPl->setState(PL_STATE::RUN);

	if (TIME_M->getWorldTime() - tempTime > .5f
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)_thisPl->setState(PL_STATE::RUN);

	//이동
	lineMove(_thisPl->getInfo().speed / 1.5);
	crossMove(_thisPl->getInfo().speed*1.5);
}

void playerDashSAttack::ExitState()
{
}
