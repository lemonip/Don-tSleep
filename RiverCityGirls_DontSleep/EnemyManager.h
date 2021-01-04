#pragma once
#include "gameNode.h"

class Enemy;

/*====================================================================
	에너미 매니저입니다. 에너미를 벡터에 넣어 관리하며,
	push로 에너미를 집어 넣을 수 있습니다.
====================================================================*/

class EnemyManager : public gameNode
{
private:
	vector<Enemy*> _vEnemy;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void pushEnemy(ENEMY_TYPE type, vector3 pos);
};

