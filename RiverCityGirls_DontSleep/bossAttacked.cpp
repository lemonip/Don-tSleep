#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	_thisBs->ChangeImg("Bs_attacked");
}

void bossAttacked::UpdateState()
{
<<<<<<< HEAD
	_thisBs->ChangeImg("attacked");
=======
	_thisBs->ChangeImg("Bs_attacked");
>>>>>>> c5860b884f4ae64a690c31b4be3f3ab795b95f7d

	
}

void bossAttacked::ExitState()
{
}
