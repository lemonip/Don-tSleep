#pragma once
#include "gameNode.h"
#include "GameObject.h"

//전방선언
class Player;
class StageManager;
class ObjectManager;
class CollisionManager;

class IEnemyState;                 // 전방선언

enum class EN_STATE
{
	EN_IDLE,                       //기본
	EN_WALK,					   //걷기
	EN_RUN,						   //뛰기
	EN_JUMP,					   //점프
	EN_LADDER,					   //사다리
	EN_LADDERTRANSITION,		   //사다리 마지막 짚고 서기
	EN_STUN,					   //기절
	EN_BEGGING,					   //구걸
	EN_DIE,						   //사망
	EN_GUARD,					   //방어
	EN_HELDRELEASE,				   //잡혔다 놓아짐
	EN_FRIEND,                     //플레이어 동료가 됨

	EN_RUNATTACK,				   //뛰다가 공격
	EN_JUMPATTACK,				   //점프 공격
	EN_HARDATTACK,				   //쎈 공격
	EN_ATTACK1,					   //처음 공격
	EN_ATTACK2,					   //처음 공격 다음 공격
	EN_ATTACK3,					   //처음 공격 다음 공격 다음 공격

	EN_DOWN,					   //쓰러짐
	EN_HELDHIT,					   //잡힌 다음 맞음
	EN_HIT,						   //맞음
	EN_WEAPONHIT,				   //무기로 맞음

	EN_WATTACK,                    //무기+공격
	EN_WIDLE,					   //무기+기본
	EN_WPICKUP,					   //무기+획득
	EN_WRUN,					   //무기+뛰기
	EN_WTHROW,					   //무기+던지기
	EN_WWALK,					   //무기+걷기
};

class Enemy : public gameNode
{
protected:

	GameObject _obj;

	struct tagInfo
	{
	public:
		RECT rcDamage;                //피격 범위 렉트 
		RECT rcAttack;				  //공격 범위 렉트 
		DIRECTION dest;				 //방향

		float gravity;               //중력
		float attack;                 //공격력
		float baseSpeed;              //최초 스피드
		float speed;                  //이동 속도
		float jumpPower;              //점프력
		float frameTimer;            //프레임시간 타이머
		float hp;					//체력

		bool isDead;               //죽었니
		bool hasWeapon;            //무기들었니
		bool goRight;              //오른쪽으로 가고있니
		bool isAttack;				//공격했니
		bool isSky;                 //공중에 있니
		bool isPhase;				//페이즈에 들어갔니
	};

	IEnemyState* _EState;
	IEnemyState* _ES_IDLE;
	IEnemyState* _ES_WALK;
	IEnemyState* _ES_RUN;
	IEnemyState* _ES_JUMP;
	IEnemyState* _ES_LADDER;
	IEnemyState* _ES_LADDERTRANSITION;
	IEnemyState* _ES_PATROL;
	IEnemyState* _ES_STUN;
	IEnemyState* _ES_BEGGING;
	IEnemyState* _ES_DIE;
	IEnemyState* _ES_GUARD;
	IEnemyState* _ES_HELDRELEASE;
	IEnemyState* _ES_FRIEND;
	IEnemyState* _ES_RUNATTACK;
	IEnemyState* _ES_JUMPATTACK;
	IEnemyState* _ES_HARDATTACK;
	IEnemyState* _ES_ATTACK1;
	IEnemyState* _ES_ATTACK2;
	IEnemyState* _ES_ATTACK3;
	IEnemyState* _ES_DOWN;
	IEnemyState* _ES_HELDHIT;
	IEnemyState* _ES_HIT;
	IEnemyState* _ES_WEAPONHIT;
	IEnemyState* _ES_WATTACK;
	IEnemyState* _ES_WIDLE;
	IEnemyState* _ES_WPICKUP;
	IEnemyState* _ES_WRUN;
	IEnemyState* _ES_WTHROW;
	IEnemyState* _ES_WWALK;
	
	ENEMY_TYPE _ENEMY_TYPE;
	EN_STATE _state;            //현재 상태 enum
	tagInfo _info;				//보스,에너미 공용 구조체

	StageManager* _stageM;		//스테이지 매니저 링크
	ObjectManager* _objectM;	//오브젝트 매니저 링크
	Player* _player;			//플래이어

public:
	virtual HRESULT init(); 
	virtual void release();
	virtual void update();
	virtual void render();

	/*====================================================================
									GETTER
	====================================================================*/
	Player* getPlayerAddress() { return _player; }
	tagInfo&    getInfo() { return _info; }

	GameObject* getObj() { return &_obj; }
	GameObject& getRefObj() { return _obj; }

	/*====================================================================
									SETTER
	====================================================================*/
	virtual void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	virtual void setPosition(vector3 pos) { _obj.pos = pos; }

	/*====================================================================
									FUNCTION
	====================================================================*/
	virtual void xzyMove(int x,int z, int y);
	virtual void SetImage();
	virtual void SetState(EN_STATE state);
	virtual void setFrame(int count, float frameInterval);
	virtual void playFrame();
};

