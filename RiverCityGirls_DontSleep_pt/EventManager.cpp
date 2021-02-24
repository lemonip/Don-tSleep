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
	�̺�Ʈ ť�� �̺�Ʈ�� �����ϸ� ù��° �̺�Ʈ�� �����Ų��.
====================================================================*/
void EventManager::update()
{
	if (_qEvent.empty()) return;					//�̺�Ʈ ť�� ��������� �����Ѵ�.

	if (_qEvent.front()->update())		//�̺�Ʈ�� �����ϰ�, ������ End�� �޴´�.
	{
		_qEvent.front()->exit();					//�ش� �̺�Ʈ�� �� ó�� �Լ��� �����ϰ�,
		SAFE_DELETE(_qEvent.front());				//�̺�Ʈ ť�� ��ü�� �����,
		_qEvent.pop();								//�̺�Ʈ ť���� �����ش�.

		if (!_qEvent.empty()) _qEvent.front()->enter(_playerControl);		//���� �̺�Ʈ�� ������ ���� ó�� �Լ��� �����Ѵ�.
	}
}

/*====================================================================
	�̺�Ʈ�� �����Ѵ�. (��ȭ ���, ��Ʈ ��� ��)
====================================================================*/
void EventManager::render(HDC hdc)
{
	if (_qEvent.empty()) return;					//�̺�Ʈ ť�� ��������� �����Ѵ�.
	_qEvent.front()->render(hdc);
}

/*====================================================================
	�̺�Ʈ ť�� �̺�Ʈ�� �߰��ϰ�, �̰� ù��°�� �ٷ� enter�� �����Ѵ�.
====================================================================*/
void EventManager::addEvent(Event * eve, bool playerControl)
{
	_playerControl = playerControl;
	eve->setLinkPlyaer(_player);
	if (_qEvent.empty()) eve->enter(_playerControl);		//�̺�Ʈ�� ��� ������ ���� ó�� �Լ��� �����Ѵ�.
	_qEvent.push(eve);						//�̺�Ʈ�� �̺�Ʈ ť�� �ִ´�.
}

/*====================================================================
	�̺�Ʈ�� �ִ���
====================================================================*/
bool EventManager::getIsEvent()
{
	return !_qEvent.empty();		//�̺�Ʈ ť�� ��� �ִ��� ��ȯ�Ѵ�.
}

/*====================================================================
	���� ��� ������
====================================================================*/
bool EventManager::getIsMovie()
{
	if (_qEvent.empty()) return false;		//�̺�Ʈ ť�� ��� ������ �ƴ϶�� �Ѵ�.
	return  _qEvent.front()->isMovie();		//���� �̺�Ʈ�� ���� ��� ������ ��ȯ�Ѵ�.
}

/*====================================================================
	ī�޶� �̵� ������ (�����ؾ� �ϴ���)
====================================================================*/
bool EventManager::getIsCameraMove()
{
	if (_qEvent.empty()) return false;		//�̺�Ʈ ť�� ��� ������ �ƴ϶�� �Ѵ�.
	return _qEvent.front()->_isCameraMove;	//���� ī�޶� �̵� ������ ��ȯ�Ѵ�.
}