#pragma once
#include"IBossState.h"


class StageManager;
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