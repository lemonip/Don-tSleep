#include "stdafx.h"
#include "EventManager.h"
#include "Player.h"

HRESULT EventManager::init()
{
	return S_OK;
}

void EventManager::release()
{
}

/*====================================================================
	이벤트 큐에 이벤트가 존재하면 첫번째 이벤트를 실행시킨다.
====================================================================*/
void EventManager::update()
{
	if (_qEvent.empty()) return;					//이벤트 큐가 비어있으면 리턴한다.

	bool isEventEnd = _qEvent.front()->update();	//이벤트를 실행하고, 끝나면 End를 받는다.

	if (isEventEnd)		//이벤트가 끝나면
	{
		_qEvent.front()->exit();					//해당 이벤트의 끝 처리 함수를 실행하고,
		SAFE_DELETE(_qEvent.front());				//이벤트 큐의 객체를 지우고,
		_qEvent.pop();								//이벤트 큐에서 지워준다.

		if (!_qEvent.empty()) _qEvent.front()->enter(_playerControl);		//다음 이벤트가 있으면 시작 처리 함수를 실행한다.
	}

}

void EventManager::render(HDC hdc)
{
	if (_qEvent.empty()) return;					//이벤트 큐가 비어있으면 리턴한다.
	_qEvent.front()->render(hdc);

}

/*====================================================================
	이벤트 큐에 이벤트를 추가하고, 이게 첫번째면 바로 enter를 실행한다.
====================================================================*/
void EventManager::addEvent(Event * eve, bool playerControl)
{
	_playerControl = playerControl;
	eve->setLinkPlyaer(_player);
	if (_qEvent.empty()) eve->enter(_playerControl);		//이벤트가 비어 있으면 시작 처리 함수를 실행한다.
	_qEvent.push(eve);						//이벤트를 이벤트 큐에 넣는다.
}

/*====================================================================
	이벤트가 있는지
====================================================================*/
bool EventManager::getIsEvent()
{
	if (_qEvent.empty()) return false;		//이벤트 큐가 비어 있으면 없다고 한다.
	else return true;						//이벤트 큐가 비어 있지 않으면 이벤트가 있다고 한다.
}

/*====================================================================
	영상 재생 중인지
====================================================================*/
bool EventManager::getIsMovie()
{
	if (_qEvent.empty()) return false;		//이벤트 큐가 비어 있으면 아니라고 한다.

	_isMovie = _qEvent.front()->isMovie();	//현재 이벤트가 영상 재생 중인지 반환한다.

	return _isMovie;
}

bool EventManager::getIsCameraMove()
{
	if (_qEvent.empty()) return false;		//이벤트 큐가 비어 있으면 아니라고 한다.

	_isMovie = _qEvent.front()->isMovie();	//현재 이벤트가 영상 재생 중인지 반환한다.

	return _isMovie;

	return false;
}
