#pragma once
#include "gameNode.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

/*====================================================================
	모든 스테이지는 에너미 매니저와 오브젝트 매니저를 가집니다.
	각각의 매니저를 사용해 스테이지에서 자유롭게 배치할 수 있도록 합니다.
====================================================================*/
class Stage : public gameNode
{
protected:
	EnemyManager* _enemyM;
	ObjectManager* _objectM;

	image* backGround;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	/*====================================================================
									GETTER
	====================================================================*/
	EnemyManager* getEnemyM() { return _enemyM; }
	ObjectManager* getObjectM() { return _objectM; }

};

