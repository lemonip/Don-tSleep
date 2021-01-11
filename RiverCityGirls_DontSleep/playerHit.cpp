#include "stdafx.h"
#include "playerHit.h"


void playerHit::EnterState()
{
	//이미지변경
	_thisPl->changeImg("pl_hit", false);


	//무기떨어뜨리기
	dropWeapon();
}

void playerHit::UpdateState()
{
}

void playerHit::ExitState()
{
}
