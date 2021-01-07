#include "stdafx.h"
#include "playerCombo1.h"

void playerCombo1::EnterState()
{
	//이미지 변경
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->changeImg("pl_comboAttack1", false);	break;
	case WEAPON_TYPE::BAT:	_thisPl->changeImg("pl_wBatAttack", false);	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}
}

void playerCombo1::UpdateState()
{
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);
	//프레임이 끝나면 공격렉트를 만들어서 충돌했는지 확인하고 데미지를 줌! 끝에하면될거같은느낌..

	//상태변경 - 공격키 누르면 2콤보 + ★몬스터와 충돌도 있어야할듯
	if (KEY_M->isOnceKeyDownV('S'))
	switch (_thisPl->getInfo().weaponType)
	{
	case WEAPON_TYPE::NONE:	_thisPl->setState(PL_STATE::COMBO2);	break;
	case WEAPON_TYPE::BAT:	break;
	case WEAPON_TYPE::BASEBALL:
		break;
	}

	
	

	//기본 동작
	basePattern();
}

void playerCombo1::ExitState()
{
}
