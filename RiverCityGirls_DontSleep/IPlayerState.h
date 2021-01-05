#pragma once
#include "gameNode.h"

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

	//업데이트정지
	bool pauseUpdate();

	//걷기동작
	void walkPattern();
	//기본동작 (걷기/약공/가드)
	void basePattern();

	//상하이동
	void lineMove(float speed);
	//좌우이동
	void crossMove(float speed);
};

