#pragma once
#include "gameNode.h"
#include "Player.h"
#include "StageManager.h"
#include "Stage.h"

class IPlayerState: public gameNode
{
protected:
	Player* _thisPl;

	bool _isCollision;	//���ʹ̿� �浹�ߴ���
	float _stateTimer;	//���°� ����Ǵ� Ÿ�̸�

public:
	IPlayerState() {}
	~IPlayerState() {}

	//�÷��̾� ��Ŀ
	void LinkPlAddress(Player* pl) { _thisPl = pl; }

	//���¸����� ����
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;

	//�ȱ⵿��
	void walkPattern();
	//�⺻���� (�ȱ�/���/����)
	void basePattern();

	//������Ʈ�� �ִ��� Ȯ��
	bool checkWeapon();

	//���ʹ̰� �ִ��� Ȯ��
	bool checkEnemy();

	//������
	void sAttack();

	//�����̵�
	void lineMove(float speed);
	//�¿��̵�
	void crossMove(float speed);
	//��ٸ� �̵�
	void ladderMove(float speed);

	//������Ʈ �Ͻ�����
	bool pauseUpdate();
	//������ ��� �������� Ȯ��, ������ �������̸� �Ű����� true
	bool isEndFrame(bool reverse);
	//���� ����߸���
	void dropWeapon();
};

