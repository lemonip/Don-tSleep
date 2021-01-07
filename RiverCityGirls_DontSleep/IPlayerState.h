#pragma once
#include "gameNode.h"
#include "Player.h"

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

	//걷기동작
	void walkPattern();
	//기본동작 (걷기/약공/가드)
	void basePattern();

	//공격상태면 공격중으로 전환
	void checkAttack();

	//상하이동
	void lineMove(float speed);
	//좌우이동
	void crossMove(float speed);

	//업데이트 일시정지
	bool pauseUpdate();
	//프레임 재생 끝났는지 확인, 리버스 프레임이면 매개변수 true
	bool isEndFrame(bool reverse);
};

