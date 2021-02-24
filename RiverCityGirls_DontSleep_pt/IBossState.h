#pragma once
#include "gameNode.h"
#include "Boss.h"
#include "Player.h"
#include "Stage.h""

class Boss;

class IBossState : public gameNode
{
protected:
	Boss* _thisBs;
	bool _isEffect;	

public:
	IBossState() {}
	~IBossState() {}

	//���� ��Ŀ
	void LinkBSAddress(Boss* bs) { _thisBs = bs; }

	//���¸����� ����
	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void ExitState() = 0;

	void LookatPlayer();
	void ResetFrame();
	void Damaged(int atk);
	void Attack();
	void collision();


};

