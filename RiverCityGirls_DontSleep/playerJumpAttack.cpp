#include "stdafx.h"
#include "playerJumpAttack.h"

void playerJumpAttack::EnterState()
{
	//방향 변경 불가
	_thisPl->setIsConDest(false);

	_thisPl->ChangeImg("pl_jumpAttack");
}

void playerJumpAttack::UpdateState()
{
	//이동
	//crossMove(_thisPl->GetInfo().speed*1.2);
}

void playerJumpAttack::ExitState()
{
}
