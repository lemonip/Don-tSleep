#pragma once
#include"IBossState.h"

class bossBlock :public IBossState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};