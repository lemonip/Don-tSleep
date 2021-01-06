#pragma once
#include"IBossState.h"

class bossWait :public IBossState
{

private: 
	int _count;			// 인터벌을 주기 위한 인트
	bool _isWait;		// 행동을 구분하기 위한 불
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
