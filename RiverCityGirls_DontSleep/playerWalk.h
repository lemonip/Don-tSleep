#pragma once
#include "IPlayerState.h"

class playerWalk :public IPlayerState
{
	float _startTime;		//키입력시간체크를 위한 시작타임
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

