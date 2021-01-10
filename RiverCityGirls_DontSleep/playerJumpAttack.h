#pragma once
#include "IPlayerState.h"

class playerJumpAttack :public IPlayerState
{
	//공격판정용
	bool _isCollsion;
	RECT _temp;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

