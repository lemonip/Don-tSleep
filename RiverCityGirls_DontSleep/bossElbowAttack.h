#pragma once
#include"IBossState.h"

class StageManager;
class Player;
class Boss;

class bossElbowAttack :public IBossState
{
private:
	int _count;
	
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};