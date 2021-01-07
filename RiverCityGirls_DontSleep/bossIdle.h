#pragma once
#include"IBossState.h"
#include"Player.h"

class bossIdle :public IBossState
{
protected:
	Player* _player;

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};