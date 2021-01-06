#pragma once
#include "IPlayerState.h"

class playerThrow : public IPlayerState
{
	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

