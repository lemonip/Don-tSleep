#pragma once
#include "gameNode.h"
#include "Player.h"

class Player;

class IPlayerState: public gameNode
{
protected:
	Player* _thisPl;

public:
	IPlayerState() {}
	~IPlayerState() {}

	//플레이어 링커
	void LinkPlAddress(Player* pl) { _thisPl = pl; }

	//상태마다의 동작
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;
};

