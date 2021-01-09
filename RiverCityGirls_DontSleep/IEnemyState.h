#pragma once
#include "gameNode.h"
#include "Enemy.h"
#include "Player.h"

class Enemy;

class IEnemyState abstract
{
protected:
	Enemy* _thisEn;
	float _stateTimer;
public:
	IEnemyState() {}
	~IEnemyState() {}

	void LinkEnemeyAddress(Enemy* en) { _thisEn = en; }

	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
};

