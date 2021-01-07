#include "stdafx.h"
#include "playerSAttack.h"

void playerSAttack::EnterState()
{
	//이미지 변경
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->changeImg("pl_sAttack", false);	break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatThrow", false);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}
	_thisPl->setIsControl(false);
}

void playerSAttack::UpdateState()
{
	//무기타입을 없음으로 변경
	if(_thisPl->getInfo().weaponType != WEAPON_TYPE::NONE)_thisPl->setWeaponType(WEAPON_TYPE::NONE);
	if (isEndFrame(false))
	{
		//키조작 가능한 상태로 변경
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttack::ExitState()
{
}
