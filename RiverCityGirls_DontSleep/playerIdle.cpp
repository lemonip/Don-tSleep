#include "stdafx.h"
#include "playerIdle.h"

void playerIdle::EnterState()
{
	//이미지 변경
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatIdle", true);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}

	}
	else _thisPl->changeImg("pl_idle", true);

	//방향조작이 가능한 상태로 변경
	_thisPl->getInfo().isConDest = true;
	//공격 상태 아님
	_thisPl->getInfo().isAttack = false;
	//타이머를 월드타이머로 맞춰서 초기화
	_stateTimer = TIME_M->getWorldTime();

	//키커맨더 벡터 비움
	KEY_M->clearVKey();
	
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
	sAttack();

	/*무기가 쫓아다님,...;;
	if (_thisPl->getInfo().attackObj)
	{
	_thisPl->getInfo().attackObj->pos.x = _thisPl->getObj().pos.x;
	_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y;
	_thisPl->getInfo().attackObj->pos.z = _thisPl->getObj().pos.z;
	}*/

	//줍기
	if (KEY_M->isOnceKeyDownV('E')) { _thisPl->setState(PL_STATE::PICK); }
		
	
}

void playerIdle::ExitState()
{
}
