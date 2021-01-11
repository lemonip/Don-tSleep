#include "stdafx.h"
#include "Enemy.h"

#include "Player.h"
#include "Stage.h"
#include "StageManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"

#include "enemyAttack1.h"
#include "enemyAttack2.h"
#include "enemyAttack3.h"
#include "enemyBegging.h"
#include "enemyDie.h"
#include "enemyDown.h"
#include "enemyGuard.h"
#include "enemyHeldHit.h"
#include "enemyHeldRelease.h"
#include "enemyHit.h"
#include "enemyIdle.h"
#include "enemyJump.h"
#include "enemyJumpAttack.h"
#include "enemyRun.h"
#include "enemyRunAttack.h"
#include "enemyStun.h"
#include "enemyWalk.h"
#include "enemyWAttack.h"
#include "enemyWeaponHit.h"
#include "enemyWIdle.h"
#include "enemyWPickup.h"
#include "enemyWRun.h"
#include "enemyWThrow.h"
#include "enemyWWalk.h"

HRESULT Enemy::init()
{
	_player = _stageM->getPlayer();
	_objectM = _stageM->getStage()->getObjectM();

	{
		_info.dest = DIRECTION::LEFT;		//방향
		_info.gravity = 0;					//중력
		_info.jumpPower = 0;				//점프력
		_info.baseSpeed = _info.speed = 3;	//속도
		_info.frameTimer = 0;				//프레임시간 타이머

		_info.hp = _info.maxHp = 30;		//체력
		_info.attack = 10;					//공격력

		_info.isAttack = _info.isSky = _info.isDead = _info.isFriend = false;
		_info.hasWeapon = false;			//무기들었니
	};

	_ES_IDLE = new enemyIdle;
	_ES_WALK = new enemyWalk;
	_ES_RUN = new enemyRun;
	_ES_JUMP = new enemyJump;
	_ES_STUN = new enemyStun;
	_ES_BEGGING = new enemyBegging;
	_ES_DIE = new enemyDie;
	_ES_GUARD = new enemyGuard;
	_ES_HELDRELEASE = new enemyHeldRelease;
	_ES_RUNATTACK = new enemyRunAttack;
	_ES_JUMPATTACK = new enemyJumpAttack;
	_ES_ATTACK1 = new enemyAttack1;
	_ES_ATTACK2 = new enemyAttack2;
	_ES_ATTACK3 = new enemyAttack3;
	_ES_DOWN = new enemyDown;
	_ES_HELDHIT = new enemyHeldHit;
	_ES_HIT = new enemyHit;
	_ES_WEAPONHIT = new enemyWeaponHit;
	_ES_WATTACK = new enemyWAttack;
	_ES_WIDLE = new enemyWIdle;
	_ES_WPICKUP = new enemyWPickup;
	_ES_WRUN = new enemyWRun;
	_ES_WTHROW = new enemyWThrow;
	_ES_WWALK = new enemyWWalk;
	_EState = NULL;

	return S_OK;
}

void Enemy::release()
{
}

void Enemy::update()
{
	_obj.prePos = _obj.pos;
	_obj.preShadow = _obj.shadow;

	_EState->UpdateState();

	_obj.update();
	_obj.shadowUpdate();

	playFrame();

	if (_info.isSky)
	{
		xzyMove(0, 0, -_info.jumpPower);
		_info.jumpPower -= GRAVITY;
	}
	else
	{
		_obj.pos.y = 0;
		_info.jumpPower = 0;
	}

	if (_state != EN_STATE::EN_DIE && _state != EN_STATE::EN_GUARD)
	{
		if (_player->getInfo().isAttack)
		{
			RECT temp;
			if (IntersectRect(&temp, &_obj.rc, &_player->getInfo().attackRc))
			{
				if(_player->getInfo().hasWeapon) SetState(EN_STATE::EN_WEAPONHIT);
				else if (_player->getInfo().state == PL_STATE::GRAB) SetState(EN_STATE::EN_HELDHIT);
				else SetState(EN_STATE::EN_HIT);
			}
		}
	}
}

void Enemy::render()
{
	if (KEY_M->isToggleKey(VK_SHIFT) && _info.isAttack)
		Rectangle(getMapDC(), _info.rcAttack);
}

void Enemy::xzyMove(int x,int z, int y)
{
	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y += y;

	_obj.shadowUpdate();

	_stageM->getColM()->enemyObjectCollision(this);

	_obj.update();
}


void Enemy::SetState(EN_STATE state)
{
	 if (_EState != NULL && _state == state) return;

	_state = state;

	if (_EState != NULL) _EState->ExitState();

	switch (_state)
	{
	case EN_STATE::EN_IDLE:             _EState = _ES_IDLE;             break;
	case EN_STATE::EN_WALK:             _EState = _ES_WALK;             break;
	case EN_STATE::EN_RUN:              _EState = _ES_RUN;              break;
	case EN_STATE::EN_JUMP:             _EState = _ES_JUMP;             break;
	case EN_STATE::EN_STUN:             _EState = _ES_STUN;             break;
	case EN_STATE::EN_BEGGING:          _EState = _ES_BEGGING;          break;
	case EN_STATE::EN_DIE:              _EState = _ES_DIE;              break;
	case EN_STATE::EN_GUARD:            _EState = _ES_GUARD;            break;
	case EN_STATE::EN_HELDRELEASE:      _EState = _ES_HELDRELEASE;      break;
	case EN_STATE::EN_RUNATTACK:        _EState = _ES_RUNATTACK;        break;
	case EN_STATE::EN_JUMPATTACK:       _EState = _ES_JUMPATTACK;       break;
	case EN_STATE::EN_ATTACK1:          _EState = _ES_ATTACK1;          break;
	case EN_STATE::EN_ATTACK2:          _EState = _ES_ATTACK2;          break;
	case EN_STATE::EN_ATTACK3:          _EState = _ES_ATTACK3;          break;
	case EN_STATE::EN_DOWN:             _EState = _ES_DOWN;             break;
	case EN_STATE::EN_HELDHIT:          _EState = _ES_HELDHIT;          break;
	case EN_STATE::EN_HIT:              _EState = _ES_HIT;              break;
	case EN_STATE::EN_WEAPONHIT:        _EState = _ES_WEAPONHIT;        break;
	case EN_STATE::EN_WATTACK:          _EState = _ES_WATTACK;          break;
	case EN_STATE::EN_WIDLE:            _EState = _ES_WIDLE;            break;
	case EN_STATE::EN_WPICKUP:          _EState = _ES_WPICKUP;          break;
	case EN_STATE::EN_WRUN:             _EState = _ES_WRUN;             break;
	case EN_STATE::EN_WTHROW:           _EState = _ES_WTHROW;           break;
	case EN_STATE::EN_WWALK:            _EState = _ES_WWALK;            break;
	default:                                                            break;
	}
	_EState->LinkEnemeyAddress(this);
	_EState->EnterState();
}


void Enemy::SetImage()
{

	switch (_state)
	{
	case EN_STATE::EN_IDLE:          if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlIdle"); }  else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyIdle"); }  else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerLeaderIdle"); }               break;
	case EN_STATE::EN_WALK:		     if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlWalk"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyWalk"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerLeaderWalk"); }               break;
	case EN_STATE::EN_RUN:			 if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlRun"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyRun"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerLeaderRun"); }               break;
	case EN_STATE::EN_JUMP:			 if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlJump"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyJump"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerLeaderJump"); }               break;
	case EN_STATE::EN_STUN:			if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlStun"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyStun"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerStun"); }               break;
	case EN_STATE::EN_BEGGING:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlBegging"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyBegging"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerBegging"); }               break;
	case EN_STATE::EN_GUARD:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlGuard"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyGuard"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerGuard"); }               break;
	case EN_STATE::EN_HELDRELEASE:	if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlHeldRelease"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyHeldRelease"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerHeldRelease"); }               break;
	//case EN_STATE::EN_FRIEND:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlFriend"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyFriend"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerFriend"); }               break;
	case EN_STATE::EN_JUMPATTACK:	if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlJumpAttack"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) {_obj.img = IMG_M->findImage("schoolBoyJumpAttack"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img =IMG_M->findImage("schoolCheerJumpAttack"); }               break;
	
	case EN_STATE::EN_RUNATTACK:	
	case EN_STATE::EN_ATTACK1:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlAttack1"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) {_obj.img = IMG_M->findImage("schoolBoyAttack1"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerAttack1"); }               break;
	case EN_STATE::EN_ATTACK2:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlAttack2"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) {_obj.img = IMG_M->findImage("schoolBoyAttack2"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerAttack2"); }               break;
	case EN_STATE::EN_ATTACK3:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlAttack3"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) {_obj.img = IMG_M->findImage("schoolBoyAttack3"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerAttack3"); }               break;
	case EN_STATE::EN_DOWN:			if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlDown"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyDown"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerDown"); }               break;
	case EN_STATE::EN_HELDHIT:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlHeldHit"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyHeldHit"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerHeldHit"); }               break;
	case EN_STATE::EN_HIT:			if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlHit"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyHit"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerHit"); }               break;
	case EN_STATE::EN_DIE:			
	case EN_STATE::EN_WEAPONHIT:	if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlWeaponHit"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyWeaponHit"); } else if (_ENEMY_TYPE == ENEMY_TYPE::CHEERLEADER) { _obj.img = IMG_M->findImage("schoolCheerWeaponHit"); }               break;
	case EN_STATE::EN_WATTACK:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlWAttack"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyWAttack"); }                break;
	case EN_STATE::EN_WIDLE:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlWIdle"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyWIdle"); }                break;
	//case EN_STATE::EN_WPICKUP:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlWPickup"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyWPickup"); }         break;
	case EN_STATE::EN_WTHROW:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlWThrow"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyWThrow"); }               break;
	case EN_STATE::EN_WWALK:		if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLGIRL) {_obj.img = IMG_M->findImage("schoolGirlWWalk"); } else if (_ENEMY_TYPE == ENEMY_TYPE::SCHOOLBOY) { _obj.img = IMG_M->findImage("schoolBoyWWalk"); }             break;
	default:																						            break;
	}
	
	
	if (_info.dest == DIRECTION::RIGHT) _obj.imgIndex.x = 0; 
	else if (_info.dest == DIRECTION::LEFT) _obj.imgIndex.x = _obj.img->getMaxFrameX();
}


	

void Enemy::setFrame(int count, float frameInterval)
{

	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 1;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 0;
		break;
	}

	if (TIME_M->getWorldTime() - _info.frameTimer > frameInterval)
	{
		_info.frameTimer = TIME_M->getWorldTime();
		switch (_info.dest)
		{
		case DIRECTION::RIGHT:
			++_obj.imgIndex.x;
			break;
		case DIRECTION::LEFT:
			--_obj.imgIndex.x;
			break;
		case DIRECTION::NONE:
			++_obj.imgIndex.x;
			break;
		}
	}
	

	switch (count)
	{
	case 0:   // 재생 후 기본 상태
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			SetState(EN_STATE::EN_IDLE);
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
		{
			SetState(EN_STATE::EN_IDLE);
		}
		break;
	case 1:        //한번 재생
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0;
		}
	}
	break;
	case 2:           //계속 재생
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = 0;
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		}
	}
	break;
	case 3:         //좌우 상관없이 계속 재생
	{
		if (_info.dest == DIRECTION::NONE && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = 0;
		}
	}
	break;
	}
}

void Enemy::playFrame()
{
	switch (_state)
	{
		//계속 재생(기본속도)
	case EN_STATE::EN_IDLE:  case EN_STATE::EN_STUN:
	case EN_STATE::EN_WALK:
	case EN_STATE::EN_WIDLE:
	case EN_STATE::EN_WWALK:
		setFrame(2, FRAMEINTERVAL);
		break;
		//계속 재생(속도 빠름)
	case EN_STATE::EN_RUN:    case EN_STATE::EN_WRUN:
		setFrame(2, FRAMEINTERVAL * 1.2);
		break;
		//한번 재생(기본속도)
	case EN_STATE::EN_JUMP:
	case EN_STATE::EN_ATTACK1: case EN_STATE::EN_ATTACK2:
		setFrame(1, FRAMEINTERVAL);
		break;
		//한번 재생(느린속도)
	case EN_STATE::EN_BEGGING: case EN_STATE::EN_GUARD:
	case EN_STATE::EN_HELDRELEASE:
	case EN_STATE::EN_JUMPATTACK:
	case EN_STATE::EN_DOWN:
	case EN_STATE::EN_HELDHIT: case EN_STATE::EN_HIT:
	case EN_STATE::EN_WEAPONHIT: case EN_STATE::EN_DIE:
		setFrame(1, FRAMEINTERVAL*1.8);
		break;
		//재생 후 기본 상태
	case EN_STATE::EN_ATTACK3:  case EN_STATE::EN_WATTACK:
	case EN_STATE::EN_WTHROW:   case EN_STATE::EN_RUNATTACK:
		setFrame(0, FRAMEINTERVAL);
		break;
	}
}