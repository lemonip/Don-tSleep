#include "stdafx.h"
#include "bossSmashAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSmashAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_smash");	
	_thisBs->getInfo().isAttack = true;
	_isEffect = false;

	LookatPlayer();
	ResetFrame();
}

void bossSmashAttack::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 1.9f)
	{
		Attack();
	}

	RECT _temp;
	/*if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getInfo().dest == DIRECTION ::LEFT)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x - 50, _thisBs->getObj()->pos.z, 50, 50);
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) 충돌처리 필요, 플레이어 렉트? 
		//손바닥 어택보다 높은 대미지
	}

	else if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x + 50, _thisBs->getObj()->pos.z, 50, 50);
		RECT _temp;
	}*/
	   	
	if (!_isEffect && IntersectRect(&_temp, &_thisBs->getInfo().rcAttack, &_thisBs->getPlayerAddress()->getRefObj().rc) && TIME_M->getWorldTime() - _enterTime > 1.9f)
	{
		EFFECT_M->play("Bss_smash", (_thisBs->getInfo().rcAttack.left + _thisBs->getInfo().rcAttack.right) / 2,
			(_thisBs->getInfo().rcAttack.top + _thisBs->getInfo().rcAttack.bottom) / 2);
		_isEffect = true;
	}

	
}

void bossSmashAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
	
}
