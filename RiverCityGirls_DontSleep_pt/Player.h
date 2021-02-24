#pragma once
#include "gameNode.h"
#include "GameObject.h"
#include "pet.h"

#define ATTACKSIZE		480			//�Ϲݰ��� ����Ʈ
#define THROWSPEED		15			//�Ϲݹ��� ������ �ӵ�


//���漱��
class StageManager;
class ObjectManager;
class EnemyManager;
class IPlayerState;
class CollisionManager;
/*====================================================================
		�÷��̾��Դϴ�. Stage�� ��ũ�Ǿ� �־�,
		���ʹ� �Ŵ���, ������Ʈ �Ŵ����� ����˴ϴ�.
====================================================================*/
//�÷��̾� ���� �̳�
enum class PL_STATE : int
{
	IDLE,			//�⺻
	WAIT,			//���
	WALK,			//�ȱ�
	RUN,			//�޸���
	JUMP,			//����
	STICK,			//�����
	CLIMB,			//������
	CLIMBTOP,		//�����ⳡ(��ٸ���)
	PICK,			//�ݱ�

	GRAB,			//���
	GUARD,			//����
	ROLL,			//������
	HIT,			//�ǰ�
	STUN,			//����
	STAND,			//���
	DOWN,			//������
	DEAD,			//���

	THROW,			//������
	STOMP,			//���
	COMBO1,			//�޺�����1
	COMBO2,			//�޺�����2
	COMBO3,			//�޺�����3

	SATTACK,		//������
	DASHATTACK,		//�뽬 ����
	DASHSATTACK,	//�뽬 ������
	JUMPATTACK,		//��������
	SATTACKDOWN		//�ٶ󺸴¹���Ű + �� + ������ (Ŀ�ǵ��Է�)
};

//������ ���� ��ġ
enum class GOALPOS
{
	PLAYER,
	WINOUT,
	FLOOR
};

//������ ���� Ÿ�� �̳�
enum class FRAMETYPE : int
{
	ONCE,
	LOOP,
	REVERSEONCE,
	REVERSELOOP
};

class Player : public gameNode
{
private:
	//���� ����ü
	struct tagInfo
	{
	public:
		GameObject* attackObj;		//���� ������Ʈ ����
		vector3 attackGoal;			//���� ������Ʈ�� ��ǥ
		RECT attackRc;				//���ݿ� ��Ʈ

		float jumpPower;			//�����Ŀ�
		float speed;				//�ӵ�

		bool hasMember;				//�ɹ����� ����
		bool hasWeapon;				//������� ����
		bool isImmune;				//�̹û�������
		bool isAttack;				//���� ����
		bool isHit;					//�¾Ҵ���
		bool isDead;				//�������
		bool isControl;				//Ű�Է� ���� ����
		bool isConDest;				//������ȯ ���� ����
		bool isSky;					//��� ����
		bool isClimb;				//��ٸ� ���� ����
		bool isRestart;				//���������

		MOVE_DIRECTION moveDest;	//�ൿ ����
		DIRECTION dest;				//�ε��� ����
		PL_STATE state;				//�÷��̾� ����
		PL_STATE preState;			//�÷��̾� ��������
		GOALPOS goalState;			//�� ����

		WEAPON_TYPE weaponType;		//��������
		int hp;					//ü��
		int maxHP;				//�ִ� ü��
		int force;				//���ݷ�
		int coin;					//������
		int	   LV;					//����
		float  exp;					//����ġ
		int hitCount;				//�ǰ� ī��Ʈ (3�������� �ٿ��)

		float immuneTimer;			//�̹�Ÿ�̸�
		float frameTimer;			//�����ӽð� Ÿ�̸�
		RENDERTYPE rendType;		//����Ÿ��
	};
private:
	tagInfo	   _info;			//�÷��̾� ����
	GameObject _obj;			//���� ������Ʈ
	RECT _temp;					//�浹��
	pet _pet;					//��

	StageManager* _stageM;		//�������� �Ŵ��� ��ũ
	ObjectManager* _objectM;	//������Ʈ �Ŵ��� ��ũ
	EnemyManager* _enemyM;		//���ʹ� �Ŵ��� ��ũ
	CollisionManager* _colM;	//�浹 �Ŵ��� ��ũ
	GameObject*		_platform;	//�÷��� ��ũ
	//�ڸɹ��� ���ʹ̸� ���� ����(�����)

private:
	//���� Ŭ����
	IPlayerState*	_IState;		//���� ����
	IPlayerState*	_idle;			//�⺻
	IPlayerState*	_wait;			//���
	IPlayerState*	_walk;			//�ȱ�
	IPlayerState*	_run;			//�޸���
	IPlayerState*	_jump;			//����
	IPlayerState*	_stick;			//�����
	IPlayerState*	_climb;			//������
	IPlayerState*	_climbTop;		//������ ��(��ٸ���)
	IPlayerState*	_pick;			//�ݱ�

	IPlayerState*	_grab;			//���
	IPlayerState*	_guard;			//����
	IPlayerState*	_roll;			//������
	IPlayerState*	_hit;			//�ǰ�
	IPlayerState*	_stun;			//����
	IPlayerState*	_stand;			//���
	IPlayerState*	_down;			//������
	IPlayerState*	_dead;			//���

	IPlayerState*	_throw;			//������
	IPlayerState*	_stomp;			//���
	IPlayerState*	_combo1;		//�޺�����1
	IPlayerState*	_combo2;		//�޺�����2
	IPlayerState*	_combo3;		//�޺�����3

	IPlayerState*	_sAttack;		//������
	IPlayerState*	_dashAttack;	//�뽬����
	IPlayerState*	_dashSAttack;   //�뽬 ������
	IPlayerState*	_jumpAttack;    //��������
	IPlayerState*	_SAttackDown;   //�ٶ󺸴¹���Ű + �� + ������ (Ŀ�ǵ��Է�)

public:
	Player() {};
	~Player() {};
	virtual HRESULT init();		//�ʱ�ȭ
	virtual void release();		//����
	virtual void update();		//������Ʈ
	virtual void render();		//����

	/*====================================================================
									GETTER
	====================================================================*/
	GameObject getObj() { return _obj; }
	GameObject& getRefObj() { return _obj; }
	GameObject* getPObj() { return &_obj; }

	tagInfo& getInfo() { return _info; }
	GameObject* getPlatform() { return _platform; }
	EnemyManager* getEnemyM() {  return _enemyM; }
	ObjectManager* getObjectM() {  return _objectM; }
	StageManager* getStageM() { return _stageM; }
	/*====================================================================
									SETTER
	====================================================================*/
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setLinkColM(CollisionManager* colM) { _colM = colM;}

	//���� ����
	void setIsControl(bool control) { _info.isControl = control; }
	//���� ����
	void setState(PL_STATE state);
	
	//�浹ó���� �ʿ��� SETTER
	void setPlatform(GameObject* platform) { _platform = platform; }
	void setJumpPower(float num) { _info.jumpPower = num;  }
	void setIsSky(bool is) { _info.isSky = is; }
	void setIsClimb(bool is) { _info.isClimb = is; }
	/*====================================================================
									FUNCTION
	====================================================================*/
	void stageInit();

	//���� �� ���� ������ ���� ������ ����
	bool isRange(GameObject obj);
	bool isRange(GameObject obj, float value);

	//���������Ʈ
	void weaponUpdate();
	//�߷��ۿ�
	void gravity();
	//Ű �Է�
	void keyInput();
	//�̹�������
	void changeImg(string imgName, bool reverse);
	//������ ����
	void setFrame(FRAMETYPE frameType, float frameInterval);
	//������ ����
	void playFrame();
	//��ǥ �̵�
	void movePos(float x, float z, float y);
	//��ǥ ����
	void setPos(float x, float z, float y);
	//�����ۿ�����Ʈ�� ��ȣ�ۿ�
	void checkItem();
	//���� ������Ʈ�� ����� ������
	bool moveAttackObj();

	//�±�
	void hit();
};
