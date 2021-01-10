#include "stdafx.h"
#include "enemyWIdle.h"
#include "Enemy.h"

void enemyWIdle::EnterState()
{
	_thisEn->SetImage();
}

void enemyWIdle::UpdateState()
{
}

void enemyWIdle::ExitState()
{
}
