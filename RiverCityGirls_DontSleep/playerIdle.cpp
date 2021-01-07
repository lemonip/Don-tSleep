#include "stdafx.h"
#include "playerIdle.h"

void playerIdle::EnterState()
{
	//이미지 변경
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->changeImg("pl_idle", true);	break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatIdle", true);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}


	//키조작 가능한 상태로 변경
	_thisPl->setIsControl(true);
	//방향조작이 가능한 상태로 변경
	_thisPl->setIsConDest(true);

	//타이머를 월드타이머로 맞춰서 초기화
	_stateTimer = TIME_M->getWorldTime();
	
}

void playerIdle::UpdateState()
{
	//일정시간동안 움직임이 없으면 기다림 상태로 전환
	if (TIME_M->getWorldTime() - _stateTimer > 3.0f)_thisPl->setState(PL_STATE::WAIT);
	//업데이트 정지 유무
	if (pauseUpdate())return;

	//기본 동작
	basePattern();
	
	//강공격
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::SATTACK);
}

void playerIdle::ExitState()
{
}
