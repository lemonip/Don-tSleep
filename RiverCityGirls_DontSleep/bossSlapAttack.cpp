#include "stdafx.h"
#include "bossSlapAttack.h"
#include "Boss.h"
#include "Player.h"

void bossSlapAttack::EnterState()
{
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_slap");

	if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getObj()->imgIndex.x = 0;
		_thisBs->getObj()->imgIndex.y = 1;
	}

	else if (_thisBs->getInfo().dest == DIRECTION::LEFT)
	{
		_thisBs->getObj()->imgIndex.x = _thisBs->getObj()->img->getMaxFrameX();
		_thisBs->getObj()->imgIndex.y = 0;
	}
}

void bossSlapAttack::UpdateState()
{	
	if ( _thisBs->getInfo().dest == DIRECTION::LEFT)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x - 50, _thisBs->getObj()->pos.z, 200, 100);
	
		/*if (IntersectRect(&_temp, &_thisBs->getInfo().rcAttack, &_thisBs->getPlayerAddress()->getObj().rc))
		{

		}*/
	}

	else if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisBs->getInfo().rcAttack = RectMakeCenter(_thisBs->getObj()->pos.x + 50, _thisBs->getObj()->pos.z, 200, 100);
			
	}	
}

void bossSlapAttack::ExitState()
{
	_thisBs->SetState(BS_STATE::IDLE);
	_thisBs->getInfo().isAttack = false;
}
