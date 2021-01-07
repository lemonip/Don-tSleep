#pragma once
#include "gameNode.h"
#include "GameObject.h"
#define GRAVITYVALUE	0.5f			//중력수치
#define JUMPPOWERVALUE  15.f			//점프파워수치
#define FRAMEINTERVAL	0.1f				//프레임인터벌

//전방선언
class StageManager;
class ObjectManager;
class EnemyManager;
class IPlayerState;
class CollisionManager;

/*====================================================================
		플래이어입니다. Stage와 링크되어 있어,
		에너미 매니저, 오브젝트 매니저와 연결됩니다.
====================================================================*/
//플레이어 상태 이넘
enum class PL_STATE : int
{
	IDLE,			//기본
	WAIT,			//대기
	WALK,			//걷기
	RUN,			//달리기
	JUMP,			//점프
	STICK,			//벽잡기
	CLIMB,			//오르기
	PICK,			//줍기

	GRAB,			//잡기
	GUARD,			//가드
	ROLL,			//구르기
	HIT,			//피격
	STUN,			//기절
	STAND,			//기상
	DOWN,			//쓰러짐
	DEAD,			//사망

	THROW,			//던지기
	STOMP,			//밟기
	COMBO1,			//콤보어택1
	COMBO2,			//콤보어택2
	COMBO3,			//콤보어택3

	SATTACK,		//강공격
	DASHATTACK,		//대쉬 공격
	DASHSATTACK,	//대쉬 강공격
	JUMPATTACK,		//점프공격
	SATTACKDOWN		//바라보는방향키 + ↓ + 강공격 (커맨드입력)
};

//플레이어 방향 이넘
enum class MOVE_DIRECTION : int
{
	LEFT,
	RIGHT,
	UP,
	DOWN
};

//프레임 실행 타입 이넘
enum class FRAMETYPE : int
{
	ONCE,
	ROOP,
	REVERSONCE,
	REVERSROOP
};

class Player: public gameNode
{
private:
	//정보 구조체
	struct tagInfo
	{
	public:
		RECT  plAttackRc;			//플레이어 공격렉트
		float jumpPower;			//점프파워
		float speed;				//속도

		bool hasMember;				//맴버소유 유무
		bool isDead;				//사망유무
		bool isControl;				//키입력 가능 유무
		bool isConDest;				//방향전환 가능 유무
		bool isSky;					//허공 유무

		MOVE_DIRECTION  moveDest;	//행동 방향
		DIRECTION dest;				//인덱스 방향
		PL_STATE state;				//플레이어 상태
		PL_STATE preState;			//플레이어 이전상태

		WEAPON_TYPE weaponType;		//무기종류
		float hp;					//체력
		float force;				//공격력
		float coin;					//소지금
		int	   LV;					//레벨
		float  exp;					//경험치
		int hitCount;				//피격 카운트 (3번맞으면 다운됨)

		float frameTimer;			//프레임시간 타이머
		RENDERTYPE rendType;		//렌더타입
		animation* ani;			//기본 애니메이션
		//★아이템벡터로 인벤토리가질듯 여기가아닐지두.. 스테이지나 플레이그라운드일 가능성있음
	};
private:
	tagInfo	   _info;			//플레이어 정보
	GameObject _obj;			//게임 오브젝트

	StageManager* _stageM;		//스테이지 매니저 링크
	ObjectManager* _objectM;	//오브젝트 매니저 링크
	EnemyManager* _enemyM;		//에너미 매니저 링크
	CollisionManager* _colM;
	GameObject*		_platform;
	//★맴버로 에너미를 가질 예정(동료로)

private:
	//상태 클래스
	IPlayerState*	_IState;		//현재 상태
	IPlayerState*	_idle;			//기본
	IPlayerState*	_wait;			//대기
	IPlayerState*	_walk;			//걷기
	IPlayerState*	_run;			//달리기
	IPlayerState*	_jump;			//점프
	IPlayerState*	_stick;			//벽잡기
	IPlayerState*	_climb;			//오르기
	IPlayerState*	_pick;			//줍기

	IPlayerState*	_grab;			//잡기
	IPlayerState*	_guard;			//가드
	IPlayerState*	_roll;			//구르기
	IPlayerState*	_hit;			//피격
	IPlayerState*	_stun;			//기절
	IPlayerState*	_stand;			//기상
	IPlayerState*	_down;			//쓰러짐
	IPlayerState*	_dead;			//사망

	IPlayerState*	_throw;			//던지기
	IPlayerState*	_stomp;			//밟기
	IPlayerState*	_combo1;		//콤보어택1
	IPlayerState*	_combo2;		//콤보어택2
	IPlayerState*	_combo3;		//콤보어택3

	IPlayerState*	_sAttack;		//강공격
	IPlayerState*	_dashAttack;	//대쉬공격
	IPlayerState*	_dashSAttack;   //대쉬 강공격
	IPlayerState*	_jumpAttack;    //점프공격
	IPlayerState*	_SAttackDown;   //바라보는방향키 + ↓ + 강공격 (커맨드입력)
public:
	Player() {};
	~Player() {};
	virtual HRESULT init();		//초기화
	virtual void release();		//해제
	virtual void update();		//업데이트
	virtual void render();		//렌더

	/*====================================================================
									GETTER
	====================================================================*/
	GameObject getObj() { return _obj; }
	tagInfo    getInfo() { return _info; }
	GameObject* getPObj() { return &_obj; }
	GameObject* getPlatform() { return _platform; }
	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setLinkColM(CollisionManager* colM) { _colM = colM; }
	//조작 유무
	void setIsControl(bool control) { _info.isControl = control; }
	//상태 지정
	void setState(PL_STATE state);
	//방향 전환 유무
	void setIsConDest(bool isConDest) { _info.isConDest = isConDest; }
	void setPlatform(GameObject* platform) { _platform = platform; }
	void setJumpPower(float num) { _info.jumpPower = num;  }
	void setIsSky(bool is) { _info.isSky = is; }
	/*====================================================================
									FUNCTION
	====================================================================*/
	void stageInit();

	//중력작용
	void gravity();
	//키 입력
	void keyInput();
	//이미지변경
	void changeImg(string imgName, bool reverse);
	//프레임 연산
	void setFrame(FRAMETYPE frameType, float frameInterval);
	//프레임 실행
	void playFrame();
	//좌표 이동
	void movePos(float x, float z, float y);
};
