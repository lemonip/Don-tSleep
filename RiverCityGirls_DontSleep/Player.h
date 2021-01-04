#pragma once
#include "gameNode.h"
#include "GameObject.h"

class StageManager;
class Stage;
class ObjectManager;
class EnemyManager;

//임시 그림자 구조체 (후에 GameObject쪽으로 옮겨질 예정.)
struct tagShadow
{
	RECT rc;
	vector3 LT, RT, RB, LB;
	vector3 pos;
};

/*====================================================================
	플래이어입니다. Stage와 링크되어 있어,
	에너미 매니저, 오브젝트 매니저와 연결됩니다.
====================================================================*/

class Player : public gameNode
{

private:
	GameObject _obj;		//게임 오브젝트

	float _jumpPower;		//점프력
	float _speed;			//속도
	int _jumpCount;			//점프 횟수

	RECT _shadowRc;			//그림자 렉트
	vector3 _shadowLT, _shadowRT, _shadowRB, _shadowLB;	//그림자 지점
	vector3 _shadowPos;		//그림자 위치
	tagShadow _shadow;		//그림자

	StageManager* _stageM;		//스테이지 매니저 링크
	ObjectManager* _objectM;	//오브젝트 매니저 링크
	EnemyManager* _enemyM;		//에너미 매니저 링크

	bool _isControl;				//키 컨트롤이 가능한지

public:

	virtual HRESULT init();		//초기화
	virtual void release();		//해제
	virtual void update();		//업데이트
	virtual void render();		//렌더

/*====================================================================
								GETTER
====================================================================*/
	GameObject getObj() { return _obj; }
	
/*====================================================================
								SETTER
====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setIsControl(bool control) { _isControl = control; }

/*====================================================================
								FUNCTION
====================================================================*/
	void move();
	void shadowUpdate();
	void stageInit();
	void keyInput();

/*====================================================================
								COLLISION
====================================================================*/
	void playerObjectCollision();

	// 전후 좌우 충돌 판정
	void LRUDCollision(GameObject* cha, tagShadow* sh, GameObject* obj);
	// 점프 판정
	void AirCollision(GameObject* cha, tagShadow* sh, GameObject* obj);

};

