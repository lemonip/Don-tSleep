#pragma once
#include "gameNode.h"
#include "Boss.h"
#include "Player.h"

class Boss;

class IBossState : public gameNode
{
protected:
	Boss* _thisBs;

public:
	IBossState() {}
	~IBossState() {}

	//보스 링커
	void LinkBSAddress(Boss* bs) { _thisBs = bs; }

	//상태마다의 동작
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;


};

