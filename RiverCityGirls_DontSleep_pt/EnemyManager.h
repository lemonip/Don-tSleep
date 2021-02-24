#pragma once
#include "gameNode.h"

class Boss;
class Enemy;
class StageManager;
/*====================================================================
	���ʹ� �Ŵ����Դϴ�. ���ʹ̸� ���Ϳ� �־� �����ϸ�,
	push�� ���ʹ̸� ���� �ְ�, pop���� �� �� �ֽ��ϴ�.
====================================================================*/

class EnemyManager : public gameNode
{
private:
	Boss* _boss;
	vector<Enemy*> _vEnemy;
	StageManager* _stageM;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pushEnemy(ENEMY_TYPE type, vector3 pos);
	void popEnemy(int index);

	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	vector<Enemy*> getVEnemy() { return _vEnemy; }

};

