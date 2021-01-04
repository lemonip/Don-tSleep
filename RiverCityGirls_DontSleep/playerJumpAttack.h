#pragma once
#include "IPlayerState.h"
#include "player.h"

class playerJumpAttack :public IPlayerState
{
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

