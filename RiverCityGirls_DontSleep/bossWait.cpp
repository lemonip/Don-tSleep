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
	if (_count % 4 == 0)
	{	
		_isWait = true;
		_thisBs->ChangeImg("idle");
	}

	/*	1. slab attack 
		2. elbow attack
		3. meteor attack
		4. dash attack
		5. smash attack
		6. bsss block
		으로 상태 행동 변화전 단계*/
		
}

void bossWait::ExitState()
{
}
