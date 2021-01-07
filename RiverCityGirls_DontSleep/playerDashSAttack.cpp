#include "stdafx.h"
#include "playerDashSAttack.h"

void playerDashSAttack::EnterState()
{
	//이미지 변경
	_thisPl->changeImg("pl_dashSAttack", false);
	//키조작 불가
	_thisPl->setIsControl(false);
}

void playerDashSAttack::UpdateState()
{
	//프레임이 다 돌면 원래 상태로 돌아가기
	//▼여기에 키안누르고있으면이라던가 추가조건해야함
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);

	
	//달리는 키를 누르고 있으면 달리는 상태로 돌아가기
	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)_thisPl->setState(PL_STATE::RUN);

	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)_thisPl->setState(PL_STATE::RUN);
		
	//이동
	/*
	lineMove(_thisPl->getInfo().speed / 1.5);
	crossMove(_thisPl->getInfo().speed*1.5);*/
}

void playerDashSAttack::ExitState()
{
}
