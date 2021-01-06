#pragma once
#include "IPlayerState.h"

class playerGrab :public IPlayerState
{
	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

