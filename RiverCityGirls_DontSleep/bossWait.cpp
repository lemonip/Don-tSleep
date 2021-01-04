#include "stdafx.h"
#include "bossWait.h"
#include "Boss.h"

void bossWait::EnterState()
{
	_count = 0;
	_count++;	
	_isWait = false;
	_thisBs->ChangeImg("idle");
	
}

void bossWait::UpdateState()
{
	if (_count % 8 == 0)
	{	
		_isWait = true;
		_thisBs->ChangeImg("idle");
	}

}

void bossWait::ExitState()
{
}
