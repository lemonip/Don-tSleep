#pragma once
#include "IPlayerState.h"


class playerCombo3: public IPlayerState
{
	//공격 충돌용
	RECT _temp;
	bool _isCollision;

public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

