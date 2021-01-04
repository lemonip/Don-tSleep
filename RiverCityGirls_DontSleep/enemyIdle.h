#pragma once
#include "IEnemyState.h"

class Enemy;

class enemyIdle : public IEnemyState
{
public :
	enemyIdle() {}
	~enemyIdle() {}

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

