#pragma once
#include "singletonBase.h"
#include <queue>
#include "Event.h"

class Player;

/*====================================================================
	이벤트를 큐에 담아 관리하는 이벤트 매니저입니다.
====================================================================*/
class EventManager : public singletonBase <EventManager>
{
private:
	queue<Event*> _qEvent;		//이벤트가 담긴 이벤트 큐

	bool _isMovie;				//영상 재생 중인지
	Player* _player;			//플래이어 링크

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
	

	/*====================================================================
									FUNCTION
	====================================================================*/
	//이벤트 추가
	void addEvent(Event* eve);		

	/*====================================================================
									SETTER
	====================================================================*/
	//플래이어와 연결
	void setLinkPlayer(Player* player) { _player = player; }

	/*====================================================================
									GETTER
	====================================================================*/
	//이벤트 존재 여부
	bool isEvent();

	//영상 재생 중인지
	bool isMovie();

};

