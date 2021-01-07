#pragma once
#include"IBossState.h"

class Player;

class bossElbowAttack :public IBossState
{
private:
	int _count;
	Player* _player;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};