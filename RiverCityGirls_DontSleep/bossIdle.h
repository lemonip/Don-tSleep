#pragma once
#include"IBossState.h"

class bossIdle :public IBossState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};