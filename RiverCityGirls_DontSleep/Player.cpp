#include "stdafx.h"
#include "Player.h"
//외부
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
//상태
#include "IPlayerState.h"
#include "playerIdle.h"
#include "playerWait.h"
#include "playerWalk.h"
#include "playerRun.h"
#include "playerJump.h"
#include "playerStick.h"
#include "playerClimb.h"
#include "playerPick.h"
#include "playerGrab.h"
#include "playerGuard.h"
#include "playerRoll.h"
#include "playerHit.h"
#include "playerStun.h"
#include "playerStand.h"
#include "playerDown.h"
#include "playerDead.h"
#include "playerThrow.h"
#include "playerStomp.h"
#include "playerCombo1.h"
#include "playerCombo2.h"
#include "playerCombo3.h"
#include "playerSAttack.h"
#include "playerDashAttack.h"
#include "playerDashSAttack.h"
#include "playerJumpAttack.h"
#include "playerSAttackDown.h"

//초기화
HRESULT Player::init()
{
	/*====================================================================
		플래이어의 오브젝트 초기화와 기본 설정을 합니다.
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("pl_wait"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2 + 200));
	_obj.imgIndex = { 0,0 };	//아직 애니메이션이 만들어지지 않아 임시로 해두었습니다.

	//기본 변수 초기화
	{
		_info.jumpPower = 0;
		_info.speed = 4.f;
		_info.hasMember = false;
		_info.isDead = false;
		_info.isControl = true;
		_info.isConDest = true;
		_info.isSky = false;
		_info.hasMember = false;
		_info.dest = DIRECTION::RIGHT;
		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info._rendType = RENDERTYPE::FRAME_RENDER;
		_info._frameTimer = TIME_M->getWorldTime();
		_info._ani = new animation;
		_info.hitCount = 3;
	}

	//상태패턴 등록
	{
		_idle = new playerIdle;
		_wait = new playerWait;
		_walk = new playerWalk;
		_run = new playerRun;
		_jump = new playerJump;
		_stick = new playerStick;
		_climb = new playerClimb;
		_pick = new playerPick;

		_grab = new playerGrab;
		_guard = new playerGuard;
		_roll = new playerRoll;
		_hit = new playerHit;
		_stun = new playerStun;
		_stand = new playerStand;
		_down = new playerDown;
		_dead = new playerDead;

		_throw = new playerThrow;
		_stomp = new playerStomp;
		_combo1 = new playerCombo1;
		_combo2 = new playerCombo2;
		_combo3 = new playerCombo3;

		_sAttack = new playerSAttack;
		_dashAttack = new playerDashAttack;
		_dashSAttack = new playerDashSAttack;
		_jumpAttack = new playerJumpAttack;
		_SAttackDown = new playerSAttackDown;
	}
	setState(PL_STATE::WAIT);

	/*====================================================================
		그림자 등 충돌 처리에 관련 해 설정합니다.
	====================================================================*/

	_shadow.pos = vector3(_obj.pos.x, _obj.pos.y, _obj.pos.z);
	_shadow.rc = RectMakeCenter(_shadow.pos.x, _shadow.pos.z, _obj.img->getWidth(), 20);
	_shadow.LT = vector3(_obj.pos.x - _obj.size.x / 2, (float)0, _obj.pos.z - 10);
	_shadow.RT = vector3(_obj.pos.x + _obj.size.x / 2, (float)0, _obj.pos.z - 10);
	_shadow.RB = vector3(_obj.pos.x + _obj.size.x / 2, (float)0, _obj.pos.z + 10);
	_shadow.LB = vector3(_obj.pos.x - _obj.size.x / 2, (float)0, _obj.pos.z + 10);
	return S_OK;
}

void Player::release()
{
}

//업뎃 순서 중요함★ 상태->중력->키입력
void Player::update()
{
	//상태업데이트
	_IState->UpdateState();
	//중력작용
	gravity();
	//키입력
	keyInput();
	//오브젝트 업뎃
	_obj.update();
	//애니프레임 업뎃
	if(_info._rendType == RENDERTYPE::ANI_RENDER)
	_info._ani->frameUpdate(TIME_M->getElapsedTime() * 10);
	//프레임업뎃
	playFrame();

}

//렌더
void Player::render()
{
	/*====================================================================
		Z-ORDER에 따라 알파 프레임 렌더 시킵니다.
	====================================================================*/

	ZORDER_M->renderObject(getMapDC(), &_obj, _info._rendType);
	Rectangle(getMapDC(), _obj.shadow.rc);
}

//상태 지정
void Player::setState(PL_STATE state)
{
	if (_info.state == state)return; //같은 상태면 변경하지 않는다.
	_info.state = state;

	//상태를 빠져나온다
	if (_IState != NULL)_IState->ExitState();

	//상태를 변경한다
	switch (_info.state)
	{
		//기본동작
	case PL_STATE::IDLE:	    _IState = _idle;		 break;
	case PL_STATE::WAIT:	    _IState = _wait;		 break;
	case PL_STATE::WALK:	    _IState = _walk;		 break;
	case PL_STATE::RUN:		    _IState = _run;			 break;
	case PL_STATE::JUMP:	    _IState = _jump;		 break;
	case PL_STATE::STICK:	    _IState = _stick;		 break;
	case PL_STATE::CLIMB:      _IState = _climb;		 break;
	case PL_STATE::PICK:      _IState = _pick;		 break;
		//가드 및 피격
	case PL_STATE::GRAB:       _IState = _grab;		 break;
	case PL_STATE::GUARD:       _IState = _guard;		 break;
	case PL_STATE::ROLL:       _IState = _roll;		 break;
	case PL_STATE::HIT:		    _IState = _hit;			 break;
	case PL_STATE::STUN:        _IState = _stun;		 break;
	case PL_STATE::STAND:		_IState = _stand;
		_info.hitCount = 3;
		break;
	case PL_STATE::DOWN:	    _IState = _down;		 break;
	case PL_STATE::DEAD:	    _IState = _dead;		 break;
		// 공격
	case PL_STATE::THROW:	    _IState = _throw;		 break;
	case PL_STATE::STOMP:	    _IState = _stomp;		 break;
	case PL_STATE::COMBO1:	    _IState = _combo1;		 break;
	case PL_STATE::COMBO2:	    _IState = _combo2;		 break;
	case PL_STATE::COMBO3:	    _IState = _combo3;		 break;
	case PL_STATE::SATTACK:     _IState = _sAttack;		 break;
	case PL_STATE::DASHATTACK:  _IState = _dashAttack;	 break;
	case PL_STATE::DASHSATTACK: _IState = _dashSAttack;  break;
	case PL_STATE::JUMPATTACK:  _IState = _jumpAttack;	 break;
	case PL_STATE::SATTACKDOWN: _IState = _SAttackDown;  break;
	default: break;
	}

	//상태 링크
	_IState->LinkPlAddress(this);
	_IState->EnterState();
}

//스테이지가 바뀔 때마다 초기화시키는 함수
void Player::stageInit()
{
	/*====================================================================
		스테이지가 바뀔 때마다 초기화시키는 함수입니다.
	====================================================================*/

	/*====================================================================
		링크 : 에너미매니저, 오브젝트 매니저와 링크합니다.
	====================================================================*/
	_enemyM = _stageM->getStage()->getEnemyM();
	_objectM = _stageM->getStage()->getObjectM();
}

//이미지 변경
void Player::changeImg(string imgName, bool reverse)
{
	//이미지를 바꾼다.
	_obj.img = IMG_M->findImage(imgName);
	//프레임 시간 갱신하여 바로 프레임 변경
	_info._frameTimer = TIME_M->getWorldTime();
	//방향과 리버스 여부 따른 프레임 x 인덱스 설정
	switch (_info.dest)
		{
		case DIRECTION::LEFT:
			if(!reverse)_obj.imgIndex.x = 0;
			else if(reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX(); 
			_obj.imgIndex.y = 0;
			break;
			
		case DIRECTION::RIGHT:
			if (!reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX(); 
			else if (reverse)_obj.imgIndex.x =0;
			_obj.imgIndex.y = 1;
			break;
		}

	
}

//프레임 연산
void Player::setFrame(FRAMETYPE frameType, float frameInterval)
{
	//프레임 y 번호 설정
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 1;
		break;
	}

	//프레임 y 번호 세팅
	_obj.img->setFrameY((int)_info.dest);

	//프레임 x 번호 조절
	switch (frameType)
	{
	case FRAMETYPE::ONCE://한 번 재생
		{
		//왼쪽의 경우 x인덱스가 0번부터~ 끝번까지 프레임이 다 되면 끝번호로 프레임번호 고정
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		//오른쪽의 경우 x인덱스가 끝번부터 0번까지 프레임이 다 되면 0번으로 프레임 번호 고정
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x <= 0)
		{
			_obj.imgIndex.x = 0; return;
		}
			
		}
		break;
	case FRAMETYPE::ROOP://무한 재생
		{
		//왼쪽의 경우 x인덱스가 0번부터~ 끝번까지 프레임이 다 되면 끝번호로 프레임번호 0번으로 갱신
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		//오른쪽의 경우 x인덱스가 끝번부터 0번까지 프레임이 다 되면 0번으로 프레임 번호 끝번호로 갱신
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x <= 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		}
		break;
	case FRAMETYPE::REVERSONCE://반대 한번 재생
		{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0)
		{
			_obj.imgIndex.x = 0; return;
		}
		}
		break;
	case FRAMETYPE::REVERSROOP://반대 무한 재생
		{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x >= _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x <= 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		
		}
		break;
	}

	cout << _obj.imgIndex.x << endl;

	//프레임 x 번호 세팅
	_obj.img->setFrameX(_obj.imgIndex.x);
	


	//프레임 실행 시간 설정
	if (TIME_M->getWorldTime() - _info._frameTimer > frameInterval)
	{
		//시간 갱신
		_info._frameTimer = TIME_M->getWorldTime();
		switch (_info.dest)
		{
		case DIRECTION::LEFT:
			if(frameType != FRAMETYPE::REVERSROOP && frameType != FRAMETYPE::REVERSONCE) ++_obj.imgIndex.x;
			else --_obj.imgIndex.x;
			
			
			break;
		case DIRECTION::RIGHT:
			if (frameType != FRAMETYPE::REVERSROOP&& frameType != FRAMETYPE::REVERSONCE) --_obj.imgIndex.x;
			else  ++_obj.imgIndex.x;
			break;
		}
	}
}

//프레임 실행
void Player::playFrame()
{
	switch (_info.state)
	{
	//무한재생 (일반 속도)
	case PL_STATE::WAIT:	case PL_STATE::STUN:
		setFrame(FRAMETYPE::ROOP, FRAMEINTERVAL);
		_info._rendType = RENDERTYPE::FRAME_RENDER;
		break;
	//반대 무한재생 (빨리)
	case PL_STATE::RUN:
		setFrame(FRAMETYPE::REVERSROOP, FRAMEINTERVAL*0.35);
		break;
	//반대 무한재생
	case PL_STATE::IDLE:	case PL_STATE::WALK:
		setFrame(FRAMETYPE::REVERSROOP, FRAMEINTERVAL);
		break;

	//한번 (천천히)
	case PL_STATE::PICK:	case PL_STATE::GRAB:					 
	
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL +2.f);
		break;
	//한번 (일반 속도)
	case PL_STATE::JUMP:	case PL_STATE::STICK:
	case PL_STATE::ROLL:
	case PL_STATE::HIT:		case PL_STATE::STAND:
	case PL_STATE::DOWN:	case PL_STATE::DEAD:
	case PL_STATE::THROW:	case PL_STATE::STOMP:
	case PL_STATE::COMBO1:	case PL_STATE::COMBO2:		
	case PL_STATE::COMBO3:	case PL_STATE::SATTACK:
	case PL_STATE::DASHATTACK:	case PL_STATE::DASHSATTACK:
	case PL_STATE::SATTACKDOWN: case PL_STATE::JUMPATTACK:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL);	
		_info._rendType = RENDERTYPE::FRAME_RENDER;
		break;
	//반대 한번재생 (빨리)
	case PL_STATE::GUARD:
		setFrame(FRAMETYPE::REVERSONCE, FRAMEINTERVAL*0.4);
		_info._rendType = RENDERTYPE::FRAME_RENDER;
		break;
	//애니랜더
	case PL_STATE::CLIMB:
		_info._rendType = RENDERTYPE::ANI_RENDER;
		_info._ani->init(_obj.img->getWidth(), _obj.img->getHeight(),
			_obj.img->getFrameWidth(), _obj.img->getFrameHeight());
		break;
	}

}

//좌표이동
void Player::movePos(float x, float z, float jumpPower)
{
	_obj.prePos = _obj.pos;

	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//그림자만 일단 한번 업데이트 (충돌처리를 위한거! 건드리면 안됨!)
	_obj.shadowUpdate();
	//충돌처리 
	_colM->objectCollision();

	//그림자 아래로 안 떨어지도록 예외처리
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//최종 렉트 갱신
	_obj.update();
}

//중력작용
void Player::gravity()
{
_info.jumpPower -= GRAVITYVALUE;
if (_obj.pos.y >= 0 && _info.isSky == true)
{
	//이전상태가 걷기나 뛰기일때만 이전상태 그대로 상태 세팅
	if (_info.preState == PL_STATE::WALK || _info.preState == PL_STATE::RUN)setState(_info.preState);
	else setState(PL_STATE::IDLE);
	_info.isSky = false;

}
if (_obj.pos.y > 0) _info.jumpPower = 0;
movePos(0, 0, _info.jumpPower);
}

//키입력
void Player::keyInput()
{
	//키조작을 못하는 상태라면 리턴
	if (!_info.isControl)return;

	//공격키받기(커맨드를위해)
	if (KEY_M->isOnceKeyDownV('D'));

	//점프
	if (KEY_M->isOnceKeyDownV('A')&& !_info.isSky)
	{
		//이전상태 저장
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWERVALUE;
		movePos(0, 0, JUMPPOWERVALUE);
	//점프파워가 - 면 점프상태로 전환
	if(_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
	}
	//구르기
	if (KEY_M->isOnceKeyDownV('W') && !_info.isSky)
	{
		//이전상태 저장
		_info.preState = _info.state;
		setState(PL_STATE::ROLL);
	}

	//방향조작을 못하는 상태라면 리턴
	if (!_info.isConDest)return;

	//왼
	if (KEY_M->isOnceKeyDownV(VK_LEFT))
	{
		_info.moveDest = MOVE_DIRECTION::LEFT;
		_info.dest = DIRECTION::LEFT;
	}
	//오
	if (KEY_M->isOnceKeyDownV(VK_RIGHT))
	{
		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
	}
	//위
	if (KEY_M->isOnceKeyDownV(VK_UP))_info.moveDest = MOVE_DIRECTION::UP;
	//아래
	if (KEY_M->isOnceKeyDownV(VK_DOWN))_info.moveDest = MOVE_DIRECTION::DOWN;


	//키커맨드 
	if (!_info.isSky && KEY_M->getVKeyBuffer().size() >= 3)
	{
		//바라보는 방향키+ ↓ + d 커맨드 공격
		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_RIGHT && _info.dest == DIRECTION::RIGHT)
			cout << "공" << endl;

		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_LEFT && _info.dest == DIRECTION::LEFT)
			cout << "공" << endl;
	}


}

