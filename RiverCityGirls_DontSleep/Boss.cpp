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
#include "bossSlabAttack.h"
#include "bossSmashAttack.h"
#include "bossStandAttack.h"
#include "IBossState.h"

HRESULT Boss::init()
{
	//기본 변수 초기화
	_info.bsWidth = 40;
	_info.bsHeight = 20;
	_info.bWidth = 50;
	_info.bHeight = 100;
	_info.angle = PI / 2;
	_info.x = WINSIZEX / 2 + 200;
	_info.z = WINSIZEY / 2;	
	_info.y = 0;
	_info.speed = 2.0f;
	_info.jumpPower = 5.0f;
	_info.count = 0;
	_info.isDead = false;
	_info.isAttack = false;
	_info.dest = BS_DEST::LEFT;
	_info.state = BS_STATE::WAIT;

	//상태패턴 등록
	_idle = new bossIdle;
	_wait = new bossWait;
	_walk = new bossMove;

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
	_slab = new bossSlabAttack;
	_smash = new bossSmashAttack;
	_standattack = new bossStandAttack;	

	_IState = _wait;
	//그림자 렉트
	_info.bssRc = RectMakeCenter(_info.x, _info.z, _info.bsWidth, _info.bsHeight);
	//보스 렉트
	_info.bsRc = RectMakeCenter(_info.x, _info.z + _info.y - _info.bHeight*0.5,
		_info.bWidth, _info.bHeight);
	return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{

	
	
}

void Boss::render()
{
	//그림자 렉트
	Ellipse(getMapDC(), _info.bssRc);
	//보스 렉트
	Rectangle(getMapDC(), _info.bsRc);
}

void Boss::SetState(BS_STATE state)
{
	if (_info.state == state)return; //같은 상태면 변경하지 않는다.
	_info.state = state;

	//상태를 빠져나온다
	if (_IState != NULL)_IState->ExitState();

	//상태를 변경한다
	switch (_info.state)
	{
		//기본동작
	case BS_STATE::IDLE:	    _IState = _idle;		 break;
	case BS_STATE::WAIT:	    _IState = _wait;		 break;
	case BS_STATE::WALK:	    _IState = _walk;		 break;
	
		//가드 및 상태변화
	case BS_STATE::GUARD:       _IState = _guard;		 break;
	case BS_STATE::ATTACKED:    _IState = _attacked;	 break;
	case BS_STATE::GROGGY:      _IState = _groggy;		 break;	
	case BS_STATE::DOWN:	    _IState = _down;		 break;
	case BS_STATE::DEAD:	    _IState = _dead;		 break;
	case BS_STATE::PHASE:		_IState = _phase;	     break;

		// 공격
	case BS_STATE::HOWLING:		_IState = _howling;		 break;
	case BS_STATE::METEOR:		_IState = _meteor;		 break;
	case BS_STATE::DASH:		_IState = _dash;		 break;
	case BS_STATE::ELBOW:		_IState = _elbow;		 break;
	case BS_STATE::SLAB:		_IState = _slab;		 break;
	case BS_STATE::SMASH:		_IState = _smash;		 break;
	case BS_STATE::STANDATTACK: _IState = _standattack;  break;

	default: break;
	}

	//상태 링크
	_IState->LinkPlAddress(this);
	_IState->EnterState();
}

void Boss::MovePos(float x, float z, float y)
{
	_info.x += x;
	_info.z += z;
	_info.y -= _info.jumpPower;

	//예외처리
	if (_info.y > 0)_info.jumpPower = 0;

	// 렉트갱신
	{
		_info.bssRc = RectMakeCenter(_info.x, _info.z, _info.bsWidth, _info.bsHeight);
		_info.bsRc = RectMakeCenter(_info.x, _info.z + _info.y - _info.bHeight*0.5,
			_info.bWidth, _info.bHeight);
	}
}

void Boss::SetAI()
{
	/*_info.count++;								미완
	if (_info.count % 8 == 0)
	{
		_boss.angle = getAngle(_boss.x, _boss.y, _player.x, _player.y);

		_boss.x += cosf(_boss.angle) * _boss.speed;
		_boss.y += -sinf(_boss.angle) * _boss.speed;
	}
	if (_palyer.x >= _boss.x)
	{

	}*/
}

void Boss::ChangeImg(string imgName)
{
	/*_info.img = IMAGEMANAGER->findImage(imgName);

	IMAGEMANAGER->addFrameImage("move",		"source/image/character/enemy/boss/move.bmp", 2110, 588, 10, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("idle",		"source/image/character/enemy/boss/idle.bmp", 3180, 634, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("block",	"source/image/character/enemy/boss/block.bmp", 1688, 576, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("attacked", "source/image/character/enemy/boss/attacked.bmp", 2214, 594, 9, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("groggy",	"source/image/character/enemy/boss/groggy.bmp", 1024, 434, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("phase",	"source/image/character/enemy/boss/phase.bmp", 5658, 748, 23, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("down",		"source/image/character/enemy/boss/down.bmp", 5830, 510, 22, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("death",	"source/image/character/enemy/boss/death.bmp", 4576, 576, 13, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("howling",	"source/image/character/enemy/boss/howling.bmp", 2916, 576, 12, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("meteor",	"source/image/character/enemy/boss/meteor_J.bmp", 1888, 672, 8, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dash",		"source/image/character/enemy/boss/tackle_L.bmp", 2882, 576, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("elbow",	"source/image/character/enemy/boss/elbow.bmp", 2915, 652, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("slab",		"source/image/character/enemy/boss/slab.bmp", 5278, 582, 14, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("smash",	"source/image/character/enemy/boss/smash.bmp", 11880, 594, 27, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("standat",	"source/image/character/enemy/boss/standattack2.bmp", 3735, 580, 15, 2, true, RGB(255, 0, 255));*/
	
}
