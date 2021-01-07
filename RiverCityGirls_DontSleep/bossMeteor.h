#pragma once
#include"IBossState.h"


class bossMeteor :public IBossState
{
private:
	int _count;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
