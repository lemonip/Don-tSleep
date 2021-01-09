#pragma once
#include "IPlayerState.h"

class playerStick :public IPlayerState
{
	float _stickTimer;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

