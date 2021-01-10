#pragma once
#include "IPlayerState.h"

class playerJumpAttack :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

