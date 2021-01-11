#pragma once
#include "IEnemyState.h"

//class Enemy;
//class Player;

class enemyIdle : public IEnemyState
{
	bool wait;
public :
	enemyIdle() {}
	~enemyIdle() {}

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

