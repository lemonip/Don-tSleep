#include "stdafx.h"
#include "playerJumpAttack.h"
#include "Player.h"

void playerJumpAttack::EnterState()
{
	//방향 변경 불가
	_thisPl->setIsConDest(false);

	_thisPl->changeImg("pl_jumpAttack");
}

void playerJumpAttack::UpdateState()
{
	//이동
	crossMove(_thisPl->getInfo().speed*1.2);
}

void playerJumpAttack::ExitState()
{
}
