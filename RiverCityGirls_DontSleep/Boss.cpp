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

#include "StageManager.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"
#include "Stage.h"
#include "StageManager.h"



HRESULT Boss::init()
{
	
	_obj.init(OBJECT_GROUP::BOSS, IMG_M->findImage("Bs_idle"), _obj.pos);
	_objectM = _stageM->getStage()->getObjectM();	
	_obj.imgIndex = { 0,0 }; 
	//상태패턴 등록
	{
		_idle = new bossIdle;
		_wait = new bossWait;
		_move = new bossMove;

		_guard = new bossBlock;
		_attacked = new bossAttacked;
		_groggy = new bossGroggy;
		_down = new bossDown;
		_dead = new bossDeath;
		_phase = new bossPhase2;

		_howling = new bossHowling;
		_meteor = new bossMeteor;
		_dash = new bossDashAttack;
		_elbow = new bossElbowAttack;
		_slap = new bossSlapAttack;
		_smash = new bossSmashAttack;
		_standattack = new bossStandAttack;
	}
	_BState = NULL;

	SetState(BS_STATE::IDLE);
	
	

	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
	_obj.update();
	_BState->UpdateState();	
	
	SetState(BS_STATE::IDLE);
	if (_player->getObj().pos.x <= _obj.pos.x)
	{
		SetDest(BS_DEST::LEFT);
	}
	else
	{
		SetDest(BS_DEST::RIGHT);
	}

	setImage();
}

void Boss::render()
{
}

void Boss::SetState(BS_STATE state)
{
	if (_BState != NULL && _state == state)return; //같은 상태면 변경하지 않는다.
	_state = state;

	//상태를 빠져나온다
	if (_BState != NULL)_BState->ExitState();

	//상태를 변경한다
	switch (_state)
	{
		//기본동작
	case BS_STATE::IDLE:	    _BState = _idle;		 break;
	case BS_STATE::WAIT:	    _BState = _wait;		 break;
	case BS_STATE::MOVE:	    _BState = _move;		 break;
	
		//가드 및 상태변화
	case BS_STATE::GUARD:       _BState = _guard;		 break;
	case BS_STATE::ATTACKED:    _BState = _attacked;	 break;
	case BS_STATE::GROGGY:      _BState = _groggy;		 break;	
	case BS_STATE::DOWN:	    _BState = _down;		 break;
	case BS_STATE::DEAD:	    _BState = _dead;		 break;
	case BS_STATE::PHASE:		_BState = _phase;	     break;

		// 공격
	case BS_STATE::HOWLING:		_BState = _howling;		 break;
	case BS_STATE::METEOR:		_BState = _meteor;		 break;
	case BS_STATE::DASH:		_BState = _dash;		 break;
	case BS_STATE::ELBOW:		_BState = _elbow;		 break;
	case BS_STATE::SLAP:		_BState = _slap;		 break;
	case BS_STATE::SMASH:		_BState = _smash;		 break;
	case BS_STATE::STANDATTACK: _BState = _standattack;  break;
	default: break;
	}

	//상태 링크
	_BState->LinkBSAddress(this);
	_BState->EnterState();
}

void Boss::SetDest(BS_DEST dest)
{
	if (_BState != NULL && _dest == dest)return; //같은 상태면 변경하지 않는다.
	_dest = dest;

	//상태를 빠져나온다
	if (_BState != NULL)_BState->ExitState();

	//상태를 변경한다
	switch (_dest)
	{
		//기본방향
	case BS_DEST::LEFT:	    _BState = _left;		break;
	case BS_DEST::RIGHT:	_BState = _right;		break;
	
	default: break;
	}
	//상태 링크
	_BState->LinkBSAddress(this);
	_BState->EnterState();

}

void Boss::setImage()
{
	switch (_state)
	{
	case BS_STATE::IDLE:          if (_ENEMY_TYPE == ENEMY_TYPE::BOSS) { IMG_M->findImage("Bs_idle"); } break;

	}
}

void Boss::stageInit()
{
	
}

void Boss::MovePos(float x, float z, float y)
{
	_obj.pos.x += x;	
	_obj.pos.z -= z;
	_obj.pos.y += y;		
}

void Boss::ChangeImg(string imgName)
{
	_obj.img = IMG_M->findImage(imgName);	
}
