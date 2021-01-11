#pragma once
#include "IEnemyState.h"

class enemyHit : public IEnemyState
{
	bool isDown;
public :

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

