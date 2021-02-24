#pragma once
#include "gameNode.h"
#include "GameObject.h"

//���漱��
class Player;
class StageManager;
class ObjectManager;
class CollisionManager;

class IEnemyState;                 // ���漱��

enum class EN_STATE
{
	EN_IDLE,                       //�⺻
	EN_WALK,					   //�ȱ�
	EN_RUN,						   //�ٱ�
	EN_JUMP,					   //����
	EN_STUN,					   //����
	EN_BEGGING,					   //����
	EN_DIE,						   //���
	EN_GUARD,					   //���
	EN_HELDRELEASE,				   //������ ������

	EN_RUNATTACK,				   //�ٴٰ� ����
	EN_JUMPATTACK,				   //���� ����
	EN_ATTACK1,					   //ó�� ����
	EN_ATTACK2,					   //ó�� ���� ���� ����
	EN_ATTACK3,					   //ó�� ���� ���� ���� ���� ����

	EN_DOWN,					   //������
	EN_HELDHIT,					   //���� ���� ����
	EN_HIT,						   //����
	EN_HIT2,
	EN_HIT3,
	EN_WEAPONHIT,				   //����� ����

	EN_WATTACK,                    //����+����
	EN_WIDLE,					   //����+�⺻
	EN_WPICKUP,					   //����+ȹ��
	EN_WRUN,					   //����+�ٱ�
	EN_WTHROW,					   //����+������
	EN_WWALK,					   //����+�ȱ�
	EN_WJUMP                       //����+����
};

class Enemy : public gameNode
{
protected:

	GameObject _obj;
	GameObject* _platform;
	struct tagInfo
	{
	public:
		RECT rcAttack;				//���� ���� ��Ʈ 
		DIRECTION dest;				//����

		float gravity;              //�߷�
		float jumpPower;            //������
		float speed;                //�̵� �ӵ�
		float baseSpeed;            //���� ���ǵ�
		float frameTimer;           //�����ӽð� Ÿ�̸�
		
		int hp;						//ü��
		int maxHp;					//�ִ� ü��
		int attack;					//���ݷ�

		bool isActive;              //�÷��̾� �߰��ߴ�
		bool isAttack;				//�����ߴ�
		bool isSky;                 //���߿� �ִ�
		bool isDead;				//�׾���
		bool isFriend;				//�����
		bool hasWeapon;				//��������	
	};
	

	IEnemyState* _EState;
	IEnemyState* _ES_IDLE;
	IEnemyState* _ES_WALK;
	IEnemyState* _ES_RUN;
	IEnemyState* _ES_JUMP;
	IEnemyState* _ES_WJUMP;
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
	IEnemyState* _ES_HIT2;
	IEnemyState* _ES_HIT3;
	IEnemyState* _ES_WEAPONHIT;
	IEnemyState* _ES_WATTACK;
	IEnemyState* _ES_WIDLE;
	IEnemyState* _ES_WPICKUP;
	IEnemyState* _ES_WRUN;
	IEnemyState* _ES_WTHROW;
	IEnemyState* _ES_WWALK;
	
	
	ENEMY_TYPE _ENEMY_TYPE;		//���ʹ� ����
	EN_STATE _state;            //���� ���� enum
	tagInfo _info;				//����

	StageManager* _stageM;		//�������� �Ŵ��� ��ũ
	ObjectManager* _objectM;	//������Ʈ �Ŵ��� ��ũ
	Player* _player;			//�÷��̾�

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
	GameObject* getPlatform() { return _platform; }
	GameObject* getObj() { return &_obj; }
	GameObject& getRefObj() { return _obj; }
	ENEMY_TYPE getEnemyType() { return _ENEMY_TYPE; }
	EN_STATE getState() { return _state; }
	ObjectManager* getObjectM() { return _objectM; }
	/*====================================================================
									SETTER
	====================================================================*/
	virtual void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	//virtual void setGoRight(bool go) { _info.goRight = go; }
	//virtual void setIsAttack(bool attack) { _info.isAttack = attack; }
	//virtual void setSpeed(float speed) { _info.speed = speed; }
	virtual void setPosition(vector3 pos) { _obj.pos = pos; }
	virtual void setPlatform(GameObject* obj) { _platform = obj; }
	/*====================================================================
									FUNCTION
	====================================================================*/
	virtual void xzyMove(int x,int z, int y);
	virtual void SetImage();
	virtual void SetState(EN_STATE state);
	virtual void setFrame(int count, float frameInterval);
	virtual void playFrame();
};

