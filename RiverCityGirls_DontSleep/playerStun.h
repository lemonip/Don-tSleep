#pragma once
#include "IPlayerState.h"

class playerStun :public IPlayerState
{
	float _stunTimer;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

