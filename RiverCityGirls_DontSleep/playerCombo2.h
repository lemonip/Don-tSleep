#pragma once
#include "IPlayerState.h"

class playerCombo2 : public IPlayerState
{
	float tempTime;	//이미지렌더 없어서 임시타이머
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};

