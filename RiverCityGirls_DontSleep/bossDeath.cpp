#include "stdafx.h"
#include "bossDeath.h"
#include "Boss.h"

void bossDeath::EnterState()
{
	
	_thisBs->ChangeImg("Bs_death");

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

void bossDeath::UpdateState()
{
	if ( _thisBs->getObj()->imgIndex.x == _thisBs->getObj()->img->getMaxFrameX() && _thisBs->getInfo().dest == DIRECTION::RIGHT)
	{			
		_thisBs->getObj()->imgIndex.x = 9;			
	}

	if (_thisBs->getObj()->imgIndex.x == 0 && _thisBs->getInfo().dest == DIRECTION::LEFT)
	{		
		_thisBs->getObj()->imgIndex.x = 3;		
	}
}

void bossDeath::ExitState()
{
}
