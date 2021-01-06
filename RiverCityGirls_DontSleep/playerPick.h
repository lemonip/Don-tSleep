#pragma once
#include "IPlayerState.h"

class playerPick : public IPlayerState
{
	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

