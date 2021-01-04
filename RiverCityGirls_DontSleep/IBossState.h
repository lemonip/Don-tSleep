#pragma once
#include "gameNode.h"
#include "Boss.h"

class Boss;

class IBossState : public gameNode
{
protected:
	Boss* _thisBs;

public:
	IBossState() {}
	~IBossState() {}

	//플레이어 링커
	void LinkPlAddress(Boss* bs) { _thisBs = bs; }

	//상태마다의 동작
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;

	void move(float speed);
	
};

