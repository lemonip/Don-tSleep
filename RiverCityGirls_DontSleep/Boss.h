#pragma once
#include "Enemy.h"

class IBossState;

enum class BS_STATE : int
{
	IDLE,			//╠Б╨╩
	WAIT,			//╢К╠Б
	MOVE,			//╟х╠Б	
	
	BLOCK,			//╟║╣Е	
	ATTACKED,		//гг╟щ
	GROGGY,			//╠в╥н╠Б		
	PHASE,			//фДюлаН
	DOWN,			//╬╡╥╞аЭ
	DEATH,			//╩Г╦а

	HOWLING,		//го©О╦╣ ╬Нец
	METEOR,			//╦чев©ю ╬Нец
	DASH,			//╢К╫╛ ╬Нец
	ELBOW,			//©╓╨╦©Л ╬Нец
	SLAP,			//╪у╧ы╢з ╬Нец
	SMASH,			//╫╨╦е╫ц ╬Нец
	STANDATTACK		//╠Б╩С ╬Нец	
	
};

class Boss : public Enemy
{
private:
	//╩Себ е╛╥║╫╨
	IBossState*	_BState;		//гЖюГ ╩Себ
	IBossState*	_idle;			//╠Б╨╩
	IBossState*	_wait;			//╢К╠Б
	IBossState*	_move;			//╟х╠Б	

	IBossState*	_block;			//╦╥╠Б	
	IBossState*	_attacked;		//гг╟щ
	IBossState*	_groggy;		//╠БюЩ	
	IBossState* _phase;			//фДюлаН2
	IBossState*	_down;			//╬╡╥╞аЭ
	IBossState*	_death;			//╩Г╦а
	
	IBossState*	_howling;		//го©О╦╣ ╬Нец
	IBossState*	_meteor;		//╦чев©ю ╬Нец
	IBossState*	_dash;			//╢К╫╛ ╬Нец
	IBossState*	_elbow;			//©╓╨╦©Л ╬Нец
	IBossState*	_slap;			//╪у╧ы╢з ╬Нец
	IBossState*	_smash;			//╫╨╦е╫ц ╬Нец
	IBossState*	_standattack;	//╠Б╩С ╬Нец
	
	DIRECTION _dest;
	BS_STATE _state;
	ENEMY_TYPE _ENEMY_TYPE;	

	RECT _rcAttack;
<<<<<<< HEAD
	float _frameTimer;
=======
	bool _isAttack;
	bool _isDown;
	bool _isWait;
	bool _isPhase;
	bool _isBlock;
	bool _isDead;
	bool _isMove;
	bool _isElbow;
	bool _isMeteor;
	bool _isSmash;
	bool _isHowling;
	bool _isDash;
>>>>>>> origin/Л┬≤М≤└Л·▒Л≈┘

	   
public:
	Boss() {};
	~Boss() {};
	virtual HRESULT init();			//цй╠Бх╜
	virtual void release();			//гьа╕
	virtual void update();			//╬В╣╚
	virtual void render();			//╥╩╢У

	//а╒╠ыюз===================================================
	Player* getPlayerAddress() { return _player; }	
	GameObject* getObj() { return &_obj; }
	GameObject getobj() { return _obj; }
	tagInfo getinfo() { return _info; }
	DIRECTION getIsDest() { return _dest; }
	
	
	//аЖа╓юз===================================================
	void SetState(BS_STATE state);
	void SetDest(DIRECTION dest);
	void setPosition(vector3 pos) { _obj.pos = pos; }	
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	

	//╠Б╢игт╪Ж===================================================
	void playFrame(int count);
	void frameUpdate();
	//void setFrame(FRAMETYPE _frametype);
	void setImage();	
	void MovePos(float x, float z, float y);				//абг╔ юл╣©
	void ChangeImg(string imgName);						//юл╧лаЖ╨╞╟Ф
	
};

