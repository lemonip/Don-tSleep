#pragma once
#include "gameNode.h"
#include "GameObject.h"
#define GRAVITYVALUE 0.5f;       //Áß·Â¼öÄ¡
#define JUMPPOWERVALUE 15.f		 //Á¡ÇÁÆÄ¿ö¼öÄ¡
#define FRAMEINTERVAL 0.1f		 //ÇÁ·¹ÀÓÀÎÅÍ¹ú

//Àü¹æ¼±¾ð
class Player;
class StageManager;
class ObjectManager;

class IEnemyState;                 // Àü¹æ¼±¾ð

enum class EN_STATE
{
	EN_IDLE,                       //±âº»
	EN_WALK,					   //°È±â
	EN_RUN,						   //¶Ù±â
	EN_JUMP,					   //Á¡ÇÁ
	EN_LADDER,					   //»ç´Ù¸®
	EN_LADDERTRANSITION,		   //»ç´Ù¸® ¸¶Áö¸· Â¤°í ¼­±â
	EN_PATROL,					   //¿Ô´Ù°¬´Ù
	EN_STUN,					   //±âÀý
	EN_BEGGING,					   //±¸°É
	EN_DIE,						   //»ç¸Á
	EN_GUARD,					   //¹æ¾î
	EN_HELDRELEASE,				   //ÀâÇû´Ù ³õ¾ÆÁü
	EN_FRIEND,                     //ÇÃ·¹ÀÌ¾î µ¿·á°¡ µÊ

	EN_RUNATTACK,				   //¶Ù´Ù°¡ °ø°Ý
	EN_JUMPATTACK,				   //Á¡ÇÁ °ø°Ý
	EN_HARDATTACK,				   //½ë °ø°Ý
	EN_ATTACK1,					   //Ã³À½ °ø°Ý
	EN_ATTACK2,					   //Ã³À½ °ø°Ý ´ÙÀ½ °ø°Ý
	EN_ATTACK3,					   //Ã³À½ °ø°Ý ´ÙÀ½ °ø°Ý ´ÙÀ½ °ø°Ý

	EN_DOWN,					   //¾²·¯Áü
	EN_HELDHIT,					   //ÀâÈù ´ÙÀ½ ¸ÂÀ½
	EN_HIT,						   //¸ÂÀ½
	EN_WEAPONHIT,				   //¹«±â·Î ¸ÂÀ½

	EN_WATTACK,                    //¹«±â+°ø°Ý
	EN_WIDLE,					   //¹«±â+±âº»
	EN_WPICKUP,					   //¹«±â+È¹µæ
	EN_WRUN,					   //¹«±â+¶Ù±â
	EN_WTHROW,					   //¹«±â+´øÁö±â
	EN_WWALK,					   //¹«±â+°È±â
};
class Enemy : public gameNode
{
protected:

	GameObject _obj;

	struct tagInfo
	{
	public:
		RECT rcDamage;                //ÇÇ°Ý ¹üÀ§ ·ºÆ® 
		RECT rcAttack;				   //°ø°Ý ¹üÀ§ ·ºÆ® 

		float gravity;               //Áß·Â
		float angle;                 //°¢µµ
		float attack;                 //°ø°Ý·Â
		float baseSpeed;              //ÃÖÃÊ ½ºÇÇµå
		float speed;                  //ÀÌµ¿¼Óµµ
		float jumpPower;              //Á¡ÇÁ·Â
		float frameTimer;            //ÇÁ·¹ÀÓ½Ã°£ Å¸ÀÌ¸Ó
		float hp;					//Ã¼·Â

		bool isDead;               //Á×¾ú´Ï
		bool weapon;              //¹«±âµé¾ú´Ï
		bool goRight;              //¿À¸¥ÂÊÀ¸·Î °¡°íÀÖ´Ï
		bool isAttack;				//°ø°ÝÇß´Ï
		bool isSky;                 //°øÁß¿¡ ÀÖ´Ï
	};
	

	//tagInfo _info;                  //¿¡³Ê¹Ì Á¤º¸

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

	DIRECTION _dest;
	ENEMY_TYPE _ENEMY_TYPE;
	EN_STATE _state;               //ÇöÀç »óÅÂ enum
<<<<<<< HEAD
		
	float _runSpeed;               //¶Ù´Â ÀÌµ¿ ¼Óµµ 
	float _walkSpeed;			   //°È´Â ÀÌµ¿ ¼Óµµ
	float _jumpPower;              //Á¡ÇÁ·Â
=======

	//int _imageXIndex;			//ÀÌ¹ÌÁö °¡·Î ÀÎµ¦½º
	//int _imageYIndex;			//ÀÌ¹ÌÁö ¼¼·Î ÀÎµ¦½º
>>>>>>> origin/ìˆ˜í˜„ìž‘ì—…
	

	StageManager* _stageM;		//½ºÅ×ÀÌÁö ¸Å´ÏÀú ¸µÅ©
	ObjectManager* _objectM;	//¿ÀºêÁ§Æ® ¸Å´ÏÀú ¸µÅ©
	Player* _player;			//ÇÃ·¡ÀÌ¾î

	tagInfo _info;			//º¸½º,¿¡³Ê¹Ì °ø¿ë ±¸Á¶Ã¼

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

	DIRECTION& getdest() { return _dest; }

	GameObject& getRefObj() { return _obj; }

	/*====================================================================
									SETTER
	====================================================================*/
	virtual void setLinkStageM(StageManager* stageM) { _stageM = stageM; }

	virtual void setPosition(vector3 pos) { _obj.pos = pos; }
	virtual void setDest(DIRECTION dest) { _dest = dest; }
	virtual void setGoRight(bool go) { _info.goRight = go; }
	virtual void setIsAttack(bool attack) { _info.isAttack = attack; }
	virtual void SetState(EN_STATE state);
	virtual void setSpeed(float speed) { _info.speed = speed; }

	/*====================================================================
									FUNCTION
	====================================================================*/
	virtual void xzyMove(int x,int z, int y);
	virtual void SetImage();
	virtual void setFrame(int count, float frameInterval);
	virtual void playFrame();
	//virtual void setBool();
};

