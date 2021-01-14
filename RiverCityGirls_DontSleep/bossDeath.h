#pragma once
#include"IBossState.h"

class bossDeath :public IBossState
{
private:
	
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};