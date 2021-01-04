#pragma once
#include"IBossState.h"

#define PI 3.14159f

class Boss;

class bossMove :public IBossState
{
private:

	int _count;
	

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};