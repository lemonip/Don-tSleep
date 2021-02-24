#pragma once
#include "singletonBase.h"
#include <queue>
#include "Event.h"

class Player;

/*====================================================================
	�̺�Ʈ�� ť�� ��� �����ϴ� �̺�Ʈ �Ŵ����Դϴ�.
====================================================================*/
class EventManager : public singletonBase <EventManager>
{
private:
	queue<Event*> _qEvent;		//�̺�Ʈ�� ��� �̺�Ʈ ť

	bool _playerControl;		//�÷��̾� ��Ʈ���� ��������
	Player* _player;			//�÷��̾� ��ũ

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);


	/*====================================================================
									FUNCTION
	====================================================================*/
	//�̺�Ʈ �߰�
	void addEvent(Event* eve, bool playerControl = false);

	/*====================================================================
									SETTER
	====================================================================*/
	//�÷��̾�� ����
	void setLinkPlayer(Player* player) { _player = player; }

	/*====================================================================
									GETTER
	====================================================================*/
	//�̺�Ʈ ���� ����
	bool getIsEvent();

	//���� ��� ������
	bool getIsMovie();

	//ī�޶� �̵� ������
	bool getIsCameraMove();

};

