#pragma once
#include "gameNode.h"

class Enemy;

class IEnemyState abstract
{
protected:
	Enemy* _thisEn;
public:
	IEnemyState() {}
	~IEnemyState() {}

	void LinkEnemeyAddress(Enemy* en) { _thisEn = en; }

	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
};

