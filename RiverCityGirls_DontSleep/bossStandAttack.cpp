#include "stdafx.h"
#include "bossStandAttack.h"

void bossStandAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_standat");
}

void bossStandAttack::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 2.0f)
	{
<<<<<<< HEAD
		_thisBs->getinfo().attackRC = RectMakeCenter(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z, 100, 100);
=======
		_thisBs->getIsInfo().rcAttack = RectMakeCenter(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z, 100, 100);
>>>>>>> origin/ìˆ˜í˜„ìž‘ì—…
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) Ãæµ¹Ã³¸® ÇÊ¿ä, ÇÃ·¹ÀÌ¾î ·ºÆ®? 
	}
}


void bossStandAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
}
