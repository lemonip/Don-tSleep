#pragma once
#include "gameNode.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

class StageManager;
/*====================================================================
	모든 스테이지는 에너미 매니저와 오브젝트 매니저를 가집니다.
	각각의 매니저를 사용해 스테이지에서 자유롭게 배치할 수 있도록 합니다.
====================================================================*/

struct tagWall
{
	vector3 LT, RT, RB, LB;
};

class Stage : public gameNode
{
protected:
	EnemyManager* _enemyM;
	ObjectManager* _objectM;
	StageManager* _stageM;

	image* backGround;
	tagWall _leftWall;
	tagWall _backWall;
	tagWall _rightWall;
	tagWall _floor;
	float _zAngle;


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
	tagWall getLeftWall() { return _leftWall; }
	tagWall getBackWall() { return _backWall; }
	tagWall getRightWall() { return _rightWall; }
	tagWall getFloor() { return _floor; }

	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }

	/*====================================================================
									디버그용 임시함수
	====================================================================*/
	void polylineRender(vector3 A, vector3 B);
	void wallRender();

};

