#pragma once
#include"IBossState.h"

class StageManager;
class Player;
class Boss;

class bossWait :public IBossState
{

private: 
	float _enterTime;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
