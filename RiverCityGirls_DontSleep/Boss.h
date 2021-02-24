#pragma once
#include "Enemy.h"

class IBossState;

enum class BS_STATE : int
{
	IDLE,			//�⺻
	WAIT,			//���
	MOVE,			//�ȱ�	
	
	BLOCK,			//����	
	ATTACKED,		//�ǰ�
	GROGGY,			//�׷α�		
	PHASE,			//������
	DOWN,			//������
	DEATH,			//���

	HOWLING,		//�Ͽ︵ ����
	METEOR,	
	METEORDOWN,		//���׿� ����
	DASH,			//�뽬 ����
	ELBOW,			//������ ����
	SLAP,			//�չٴ� ����
	SMASH,			//���Ž� ����
	STANDATTACK		//��� ����	
	
};

class Boss : public Enemy
{
private:
	//���� Ŭ����
	IBossState*	_BState;		//���� ����
	IBossState*	_idle;			//�⺻
	IBossState*	_wait;			//���
	IBossState*	_move;			//�ȱ�	
	IBossState*	_block;			//����	
	IBossState*	_attacked;		//�ǰ�
	IBossState*	_groggy;		//����	
	IBossState* _phase;			//������2
	IBossState*	_down;			//������
	IBossState*	_death;			//���	
	IBossState*	_howling;		//�Ͽ︵ ����
	IBossState*	_meteor;		//���׿� ����
	IBossState*	_dash;			//�뽬 ����
	IBossState*	_elbow;			//������ ����
	IBossState*	_slap;			//�չٴ� ����
	IBossState*	_smash;			//���Ž� ����
	IBossState*	_standattack;	//��� ����
	IBossState* _meteordown;
	
	bool _isPhase;				//����� ����
	int _groggyCount;			
	int _phaseCount;					

	BS_STATE _state;
	ENEMY_TYPE _ENEMY_TYPE;	
	float _frameTimer;

public:
	Boss() {};
	~Boss() {};
	virtual HRESULT init();			//�ʱ�ȭ
	virtual void release();			//����
	virtual void update();			//����
	virtual void render();			//����

	//������===================================================
	bool getIsphase() { return _isPhase; }
	BS_STATE getState() {return _state;}
	int& getGroggyCount() { return _groggyCount; }
	int& getPhaseCount() { return _phaseCount; }
	//������===================================================
	void SetState(BS_STATE state);
	void SetDest(DIRECTION dest);
	void setPosition(vector3 pos) { _obj.pos = pos; }	
	void setLinkStageM(StageManager* stageM) { _stageM = stageM; }
	void setIsphase(bool isphase) { _isPhase = isphase; }

	//����Լ�===================================================
	void playFrame(int count);
	void frameUpdate();	
	void ChangeImg(string imgName);						//�̹�������	
};

