#include "stdafx.h"

#include "Boss.h"
#include "bossMeteor.h"
#include "bossAttacked.h"
#include "bossBlock.h"
#include "bossDashAttack.h"
#include "bossDeath.h"
#include "bossDown.h"
#include "bossElbowAttack.h"
#include "bossGroggy.h"
#include "bossHowling.h"
#include "bossIdle.h"
#include "bossWait.h"
#include "bossMove.h"
#include "bossPhase2.h"
#include "bossSlapAttack.h"
#include "bossSmashAttack.h"
#include "bossStandAttack.h"
#include "IBossState.h"

#include "CollisionManager.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"

HRESULT Boss::init()
{
	_player = _stageM->getPlayer();
	_objectM = _stageM->getStage()->getObjectM();

	_obj.init(OBJECT_GROUP::BOSS, IMG_M->findImage("Bs_idle"), _obj.pos);	
	_obj.imgIndex = { 0,0 };
	
	_frameTimer = TIME_M->getWorldTime();
	
	_info.dest = DIRECTION::LEFT;		//����
	_info.gravity = 0;					//�߷�
	_info.jumpPower = 0;				//������
	_info.baseSpeed = _info.speed = 3;	//�ӵ�
	_info.frameTimer = 0;				//�����ӽð� Ÿ�̸�

	_info.hp = _info.maxHp = 3000;		//ü��
	_info.attack = 10;					//���ݷ�
	_groggyCount = 0;
	_phaseCount = 0;

	_info.isAttack = _info.isSky = _info.isDead = _info.isFriend = false;
	_info.hasWeapon = false;			//��������	

	//�������� ���
	_idle = new bossIdle;
	_wait = new bossWait;
	_move = new bossMove;

	_block = new bossBlock;
	_attacked = new bossAttacked;
	_groggy = new bossGroggy;
	_down = new bossDown;
	_death = new bossDeath;
	_phase = new bossPhase2;

	_howling = new bossHowling;
	_meteor = new bossMeteor;
	_dash = new bossDashAttack;
	_elbow = new bossElbowAttack;
	_slap = new bossSlapAttack;
	_smash = new bossSmashAttack;
	_standattack = new bossStandAttack;
	
	_info.isAttack = false;	
	_isPhase = false;

	_BState = NULL;

	SetState(BS_STATE::IDLE);


	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	_obj.prePos = _obj.pos;
	_obj.preShadow = _obj.shadow;
	_BState->UpdateState();	
	_obj.update();
	_obj.shadowUpdate();
	frameUpdate();		
	_stageM->getColM()->bossDestructObject(this);

	//cout << _player->getInfo().hp << endl;

	if (KEY_M->isOnceKeyDown('V')) SetState(BS_STATE::SMASH);
	if (KEY_M->isOnceKeyDown('B')) SetState(BS_STATE::GROGGY);
	if (KEY_M->isOnceKeyDown('N')) SetState(BS_STATE::PHASE);
	if (KEY_M->isOnceKeyDown('M')) SetState(BS_STATE::HOWLING);
}

void Boss::render()
{		
	if (KEY_M->isToggleKey(VK_SHIFT) && _info.isAttack) Rectangle(getMapDC(), _info.rcAttack);	
}

void Boss::SetState(BS_STATE state)
{
	if (_BState != NULL && _state == state) return; //���� ���¸� �������� �ʴ´�.
	_state = state;

	//���¸� �������´�
	if (_BState != NULL)_BState->ExitState();

	//���¸� �����Ѵ�
	switch (_state)
	{
		//�⺻����
	case BS_STATE::IDLE:	    _BState = _idle;		 break;
	case BS_STATE::WAIT:	    _BState = _wait;		 break;
	case BS_STATE::MOVE:	    _BState = _move;		 break;
	
		//���� �� ���º�ȭ
	case BS_STATE::BLOCK:       _BState = _block;		 break;
	case BS_STATE::ATTACKED:    _BState = _attacked;	 break;
	case BS_STATE::GROGGY:      _BState = _groggy;		 break;	
	case BS_STATE::DOWN:	    _BState = _down;		 break;
	case BS_STATE::DEATH:	    _BState = _death;		 break;
	case BS_STATE::PHASE:		_BState = _phase;	     break;

		// ����
	case BS_STATE::HOWLING:		_BState = _howling;		 break;
	case BS_STATE::METEOR:		_BState = _meteor;		 break;
	case BS_STATE::DASH:		_BState = _dash;		 break;
	case BS_STATE::ELBOW:		_BState = _elbow;		 break;
	case BS_STATE::SLAP:		_BState = _slap;		 break;
	case BS_STATE::SMASH:		_BState = _smash;		 break;
	case BS_STATE::STANDATTACK: _BState = _standattack;  break;
	default: break;
	}

	//���� ��ũ
	_BState->LinkBSAddress(this);
	_BState->EnterState();
}

void Boss::SetDest(DIRECTION dest)
{
	if (_info.dest == dest)return; //���� ���¸� �������� �ʴ´�.
	_info.dest = dest;
}

void Boss::frameUpdate()
{
	if (TIME_M->getWorldTime() - _frameTimer > 0.1f)
	{
		_frameTimer = TIME_M->getWorldTime();

		switch (_state)
		{
		case BS_STATE::IDLE:		
		case BS_STATE::DEATH:
		case BS_STATE::MOVE:
		case BS_STATE::WAIT:
		case BS_STATE::GROGGY:	
		case BS_STATE::DOWN:
		case BS_STATE::METEORDOWN:
		playFrame(0);
		break;

		case BS_STATE::METEOR:						
		playFrame(1);
		break;

		case BS_STATE::DASH:
		case BS_STATE::BLOCK:
		case BS_STATE::SMASH:
		case BS_STATE::SLAP:
		case BS_STATE::ELBOW:
		case BS_STATE::PHASE:
		case BS_STATE::HOWLING:
		case BS_STATE::ATTACKED:
		case BS_STATE::STANDATTACK:		
		playFrame(-1);
		break;

		default:
		break;
		}
	}
}

void Boss::playFrame(int count)
{
	switch (count)
	{
	case -1:	//�� �� ��� �� �⺻				
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = 0;
			SetState(BS_STATE::IDLE);			
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0)
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
			SetState(BS_STATE::IDLE);			
		}
		break;

	case 1:		//�� ���� ���
	
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX()) _obj.imgIndex.x = _obj.img->getMaxFrameX();
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0) _obj.imgIndex.x = 0;
		break;

	case 0:		//���� ���
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX()) _obj.imgIndex.x = 0;
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0) _obj.imgIndex.x = _obj.img->getMaxFrameX();
		break;
	}
	
	switch (_info.dest)
	{
	case DIRECTION::LEFT: 
		_obj.imgIndex.x--;
		_obj.imgIndex.y = 0;
		break;
		
	case DIRECTION::RIGHT: 
		++_obj.imgIndex.x;
		_obj.imgIndex.y = 1;
		break;
	}
}

void Boss::ChangeImg(string imgName)
{
	_obj.img = IMG_M->findImage(imgName);	
}

