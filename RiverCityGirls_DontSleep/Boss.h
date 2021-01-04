#pragma once
#include "gameNode.h"
#include "IBossState.h"
#include "Enemy.h"

#define PI 3.14159f

enum class BS_STATE : int
{
	IDLE,			//기본
	WAIT,			//대기
	WALK,			//걷기	
	
	GUARD,			//가드	
	ATTACKED,		//피격
	GROGGY,			//그로기		
	PHASE,			//페이즈
	DOWN,			//쓰러짐
	DEAD,			//사망

	HOWLING,		//하울링 어택
	METEOR,			//메테오 어택
	DASH,			//대쉬 어택
	ELBOW,			//엘보우 어택
	SLAB,			//손바닥 어택
	SMASH,			//스매시 어택
	STANDATTACK		//기상 어택	
	
};

//보스 방향
enum class BS_DEST : int
{
	RIGHT,
	LEFT
};

//전방선언
class IBossState;	//보스 상태

class Boss : public Enemy
{
private:

	//정보 구조체
	struct tagInfo
	{
	public:
		image* img;
		int count;
		float angle;
		float bsWidth, bsHeight;	//그림자 가로세로
		float bWidth, bHeight;		//플레이어 가로세로
		float x, z, y;				//좌표
		float jumpPower;			//점프파워
		float speed;				//속도
		float damage;				//데미지		
		bool isAttack;				//공격 시작 유무
		bool isDead;				//사망유무		
		RECT bssRc;					//그림자 렉트
		RECT bsRc;					//보스 렉트
		BS_STATE state;				//보스 상태
		BS_DEST dest;				//방향
	};

	tagInfo _info;		
	

private:
	//상태 클래스
	IBossState*	_IState;		//현재 상태
	IBossState*	_idle;			//기본
	IBossState*	_wait;			//대기
	IBossState*	_walk;			//걷기	

	IBossState*	_guard;			//가드	
	IBossState*	_attacked;		//피격
	IBossState*	_groggy;		//기절	
	IBossState* _phase;			//페이즈2
	IBossState*	_down;			//쓰러짐
	IBossState*	_dead;			//사망
	
	IBossState*	_howling;		//하울링 어택
	IBossState*	_meteor;		//메테오 어택
	IBossState*	_dash;			//대쉬 어택
	IBossState*	_elbow;			//엘보우 어택
	IBossState*	_slab;			//손바닥 어택
	IBossState*	_smash;			//스매시 어택
	IBossState*	_standattack;	//기상 어택


public:
	//기본함수===================================================
	virtual HRESULT init();			//초기화
	virtual void release();			//해제
	virtual void update();			//업뎃
	virtual void render();			//렌더

	//접근자===================================================
	tagInfo& GetInfo() { return _info; }
	RECT&	 GetSRc() { return _info.bssRc; }
	RECT&	 GetRc() { return _info.bsRc; }

	//지정자===================================================
	void SetState(BS_STATE state);

	//기능함수===================================================
	void MovePos(float x, float z, float y);				//좌표 이동
	void SetAI();										//AI 설정
	void ChangeImg(string imgName);						//이미지변경

};

