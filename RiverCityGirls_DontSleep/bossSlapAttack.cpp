#include "stdafx.h"
#include "bossSlapAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSlapAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_slap");
}

void bossSlapAttack::UpdateState()
{
	
		
	if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getobj().pos.x > _thisBs->getPlayerAddress()->getObj().pos.x)
	{
<<<<<<< HEAD
		_thisBs->getinfo().attackRC = RectMakeCenter(_thisBs->getobj().pos.x - 10, _thisBs->getobj().pos.z, 20, 20);
=======
		_thisBs->getIsInfo().rcAttack = RectMakeCenter(_thisBs->getobj().pos.x - 10, _thisBs->getobj().pos.z, 20, 20);
>>>>>>> origin/ìˆ˜í˜„ìž‘ì—…
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) Ãæµ¹Ã³¸® ÇÊ¿ä, ÇÃ·¹ÀÌ¾î ·ºÆ®? 
	}

	else if (TIME_M->getWorldTime() - _enterTime > 3.0f && _thisBs->getobj().pos.x < _thisBs->getPlayerAddress()->getObj().pos.x)
	{
<<<<<<< HEAD
		_thisBs->getinfo().attackRC = RectMakeCenter(_thisBs->getobj().pos.x - 10, _thisBs->getobj().pos.z, 20, 20);
=======
		_thisBs->getIsInfo().rcAttack = RectMakeCenter(_thisBs->getobj().pos.x - 10, _thisBs->getobj().pos.z, 20, 20);
>>>>>>> origin/ìˆ˜í˜„ìž‘ì—…
		RECT _temp;		
	}	
}

void bossSlapAttack::ExitState()
{
	return;
	_thisBs->SetState(BS_STATE::IDLE);
}
