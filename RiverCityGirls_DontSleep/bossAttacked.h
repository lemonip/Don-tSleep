#pragma once
#include"IBossState.h"

class bossAttacked :public IBossState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};