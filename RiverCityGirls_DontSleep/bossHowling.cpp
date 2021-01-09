#include "stdafx.h"
#include "bossHowling.h"
#include "Boss.h"
#include "Player.h"

void bossHowling::EnterState()
{	
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_howling");
}

void bossHowling::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 8.0f)
	{
<<<<<<< HEAD
		_thisBs->getinfo().attackRC = RectMakeCenter(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z, 100, 100);
=======
		_thisBs->getIsInfo().rcAttack = RectMakeCenter(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z, 100, 100);
>>>>>>> origin/ìˆ˜í˜„ìž‘ì—…
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) Ãæµ¹Ã³¸® ÇÊ¿ä, ÇÃ·¹ÀÌ¾î ·ºÆ®? 
		// Áö¼Ó Ã³¸® ÇÊ¿ä
	}	
}

void bossHowling::ExitState()
{
	return;

	_thisBs->SetState(BS_STATE::IDLE);
}
