#include "stdafx.h"
#include "Player.h"

#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"

#include "IPlayerState.h"
#include "playerIdle.h"
#include "playerWait.h"
#include "playerWalk.h"
#include "playerRun.h"
#include "playerJump.h"
#include "playerStick.h"
#include "playerLadder.h"
#include "playerGuard.h"
#include "playerRoll.h"
#include "playerHit.h"
#include "playerStun.h"
#include "playerStand.h"
#include "playerDown.h"
#include "playerDead.h"
#include "playerStomp.h"
#include "playerCombo1.h"
#include "playerCombo2.h"
#include "playerCombo3.h"
#include "playerSAttack.h"
#include "playerDashAttack.h"
#include "playerDashSAttack.h"
#include "playerJumpAttack.h"
#include "playerSAttackDown.h"

HRESULT Player::init()
{
	/*====================================================================
		플래이어의 오브젝트 초기화와 기본 설정을 합니다.
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("pl_wallet"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2));
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
	_ladder = new playerLadder;

	_guard = new playerGuard;
	_roll = new playerRoll;
	_hit = new playerHit;
	_stun = new playerStun;
	_stand = new playerStand;
	_down = new playerDown;
	_dead = new playerDead;

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


	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	//키입력
	keyInput();
	//중력작용
	gravity();
	//상태업데이트
	_IState->UpdateState();

	_obj.update();
}

void Player::render()
{
	/*====================================================================
		Z-ORDER에 따라 알파 프레임 렌더 시킵니다.
	====================================================================*/
	ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
	Rectangle(getMapDC(), _obj.shadow.rc);
	//(아직 플래이어 애니메이션이 없어 임시로 해두었습니다. 나중에 ANI_RENDER로 바꿔서 쓰세요!)
}




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
	case PL_STATE::LADDER:      _IState = _ladder;		 break;
		//가드 및 피격
	case PL_STATE::GUARD:       _IState = _guard;		 break;
	case PL_STATE::HIT:		    _IState = _hit;			 break;
	case PL_STATE::STUN:        _IState = _stun;		 break;
	case PL_STATE::STAND:
		_IState = _stand;
		_info.hitCount = 3;
		break;
	case PL_STATE::DOWN:	    _IState = _down;		 break;
	case PL_STATE::DEAD:	    _IState = _dead;		 break;
		// 공격
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
	//그림자 밑으로 떨어질 때 예외처리
	if (_obj.pos.y > 0) _info.jumpPower = 0;
	//좌표 갱신
	MovePos(0, 0, _info.jumpPower);
}

void Player::keyInput()
{

	//키조작을 못하는 상태라면 리턴
	if (!_info.isControl)return;

	//공격키받기(커맨드를위해)
	if (KEY_M->isOnceKeyDownV('D'));

	//점프
	if (KEY_M->isOnceKeyDownV('A') && !_info.isSky)
	{
		//이전상태 저장
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWERVALUE;
		MovePos(0, 0, JUMPPOWERVALUE);
		//점프파워가 - 면 점프상태로 전환
		if (_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
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

void Player::ChangeImg(string imgName)
{
	_obj.img = IMG_M->findImage(imgName);
	//_obj.img->setFrameY((int)_info.indexDest);//여기말고 프레임렌더에있어야함
	//if (_info.indexDest == DIRECTION::LEFT) _obj.img->setFrameX(0);
	//else if (_info.indexDest == DIRECTION::RIGHT) _obj.img->setFrameX(_obj.img->getMaxFrameX());

	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 1;
		break;
	}

		_obj.img->setFrameY((int)_obj.imgIndex.y);//여기말고 프레임렌더에있어야함
	if (_info.dest == DIRECTION::LEFT) _obj.img->setFrameX(0);
	else if (_info.dest == DIRECTION::RIGHT) _obj.img->setFrameX(_obj.img->getMaxFrameX());

}

//좌표이동
void Player::MovePos(float x, float z, float jumpPower)
{
	_obj.prePos = _obj.pos;

	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//그림자만 일단 한번 업데이트
	_obj.shadowUpdate();
	//충돌처리
	_colM->Collision();

	//그림자 아래로 안 떨어지도록 예외처리
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//최종 렉트 갱신
	_obj.update();
}
