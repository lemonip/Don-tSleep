#pragma once
#include "IEnemyState.h"
class enemyWAttack : public IEnemyState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

