#include "stdafx.h"
#include "bossSlapAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSlapAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_slap");
	_thisBs->getInfo().isAttack = true;

	LookatPlayer();
	ResetFrame();	
}

void bossSlapAttack::UpdateState()
{	
	if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getInfo().rcAttack = RectMake(_thisBs->getObj()->pos.x + 80, _thisBs->getObj()->pos.z - 200, 150, 200);
	}
	else if (_thisBs->getInfo().dest == DIRECTION::LEFT)
	{
		_thisBs->getInfo().rcAttack = RectMake(_thisBs->getObj()->pos.x - 80, _thisBs->getObj()->pos.z - 200, 150, 200);
	}		

	EFFECT_M->play("Bss_attack", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
		(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
}


void bossSlapAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
