#pragma once
#include "IPlayerState.h"

class playerIdle :public IPlayerState
{
	float _stateTimer;	//상태가 변경되는 타이머
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

