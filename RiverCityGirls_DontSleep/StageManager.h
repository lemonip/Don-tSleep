#pragma once

class Player;
class Stage;

/*====================================================================
	StageManager는, 플래이어와 스테이지를 멤버로 가지며,
	스테이지에는 Easy, Normal, Hard, Boss가 있습니다.
	스테이지는 '현재 스테이지 상태'로 간주하며, 상태 패턴으로 관리합니다.
====================================================================*/

class StageManager
{
	Player* _player;
	Stage* _stage;
	STAGETYPE _currentStage;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();	
	virtual void render();

	/*====================================================================
									SETTER
	====================================================================*/
	virtual void setStage(STAGETYPE current);


	/*====================================================================
									GETTER
	====================================================================*/
	Stage* getStage() { return _stage; }
	Player* getPlayer() { return _player; }

};

