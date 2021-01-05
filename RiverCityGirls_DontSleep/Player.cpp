#include "stdafx.h"
#include "Player.h"
//외부
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
//상태
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

//초기화
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
		_info._frameTimer = TIME_M->getWorldTime();

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

	////////////////////////////////////////얘들 어떻게해야해? ▼▼▼▼▼▼
	//move();
	shadowUpdate();
	_obj.update(); //요기하나
	playerObjectCollision();
	shadowUpdate();
	_obj.update(); //이거 왜 두개..? 
}

void Player::render()
{
	/*====================================================================
		Z-ORDER에 따라 알파 프레임 렌더 시킵니다.
	====================================================================*/
	ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
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

void Player::shadowUpdate()
{
	_shadow.pos = vector3(_obj.pos.x, _obj.pos.y, _obj.pos.z);
	_shadow.rc = RectMakeCenter(_shadow.pos.x, _shadow.pos.z, _obj.img->getWidth(), 20);
	_shadow.LT = vector3(_obj.pos.x - _obj.size.x / 2, (float)0, _obj.pos.z - 10);
	_shadow.RT = vector3(_obj.pos.x + _obj.size.x / 2, (float)0, _obj.pos.z - 10);
	_shadow.RB = vector3(_obj.pos.x + _obj.size.x / 2, (float)0, _obj.pos.z + 10);
	_shadow.LB = vector3(_obj.pos.x - _obj.size.x / 2, (float)0, _obj.pos.z + 10);
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
void Player::changeImg(string imgName)
{
	//이미지를 바꾼다.
	_obj.img = IMG_M->findImage(imgName);
	//프레임 시간 갱신
	_info._frameTimer = TIME_M->getWorldTime();
	//방향에 따른 이미지의 x,y변수 변경
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.x = 0;
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.x = _obj.img->getMaxFrameX();
		_obj.imgIndex.y = 1;
		break;
	}
	//프레임 실행 방식 설정


	//여기말고 프레임렌더에있어야함
	_obj.img->setFrameY((int)_obj.imgIndex.y);
	if (_info.dest == DIRECTION::LEFT) _obj.img->setFrameX(0);
	else if (_info.dest == DIRECTION::RIGHT) _obj.img->setFrameX(_obj.img->getMaxFrameX());

}

//프레임 재생
void Player::playFrame()
{
}

//좌표이동
void Player::movePos(float x, float z, float jumpPower)
{
	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//그림자 아래로 안 떨어지도록 예외처리
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//렉트갱신
	_obj.RectRenew();
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
	if (KEY_M->isOnceKeyDownV('A'))// <<얘는 다되요 ㅠㅠ
	{
		//이전상태 저장
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWERVALUE;
		movePos(0, 0, JUMPPOWERVALUE);
	//점프파워가 - 면 점프상태로 전환
	if(_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
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


void Player::move()
{
	_obj.prePos = _obj.pos;

	_obj.pos.y -= _info.jumpPower;
	if (_obj.pos.y > _info.jumpPower)_info.jumpPower = 0;
	if (_obj.pos.y < 0) _info.jumpPower -= GRAVITY;

	if (_info.jumpPower == 0) _info.isSky = true;
}
void Player::playerObjectCollision()
{
	for (int i = 0; i < _objectM->getVObject().size(); ++i)
	{
		GameObject* obs = _objectM->getVObject()[i]->getObj();
		if (obs->group == OBJECT_GROUP::OBJECT)
		{
			AirCollision(&_obj, &_shadow, obs);
		}
	}
}
void Player::LRUDCollision(GameObject* cha, tagShadow* sh, GameObject* obj)
{
	if (obj->group == OBJECT_GROUP::OBJECT)
	{
		vector3 interVector; // 교차점을 담을 벡터
		if (cha->prePos.x < cha->pos.x && cha->prePos.z == cha->pos.z) // 플레이어가 오른쪽으로 움직였을 때
		{
			if (obj->bottomPlane[3].getEnd().z < sh->RB.z &&
				sh->RT.z < obj->bottomPlane[3].getStart().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
			{
				if (Linear(sh->RT, sh->RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // 우측 선분이 좌측변이랑 교차하면
					Linear(sh->RT, sh->RB).segmentIntersect(obj->bottomPlane[2], &interVector))	// 우측 선분이 밑변이랑 교차하면
				{
					if (sh->RB.z < obj->bottomPlane[3].getStart().z) // 그림자 밑변이 오브젝트 밑변보다 위에 있을 경우
					{
						cha->pos.x = obj->bottomPlane[3].getX(sh->RB.z) - cha->size.x / 2; // 교차 점에서 왼쪽으로 보정
					}
					else // 그림자 밑변이 오브젝트 밑변보다 아래에 있을 경우
					{
						cha->pos.x = obj->bottomPlane[3].getStart().x - cha->size.x / 2;
					}
				}
			}
		}
		else if (cha->pos.x < cha->prePos.x && cha->prePos.z == cha->pos.z) // 플레이어가 왼쪽으로 움직였을 때
		{
			if (obj->bottomPlane[1].getStart().z < sh->LB.z &&
				sh->LT.z < obj->bottomPlane[1].getEnd().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
			{
				if (Linear(sh->LT, sh->LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // 좌측 선분이 우측변이랑 교차하
					Linear(sh->LT, sh->LB).segmentIntersect(obj->bottomPlane[0], &interVector))    // 좌측 선분이 윗밑변이랑 교차하면
				{
					if (obj->bottomPlane[1].getStart().z < sh->LT.z) // 그림자 윗변이 오브젝트 윗변보다 아래에 있을 경우
					{
						cha->pos.x = obj->bottomPlane[1].getX(sh->LT.z) + cha->size.x / 2; // 교차 점에서 왼쪽으로 보정
					}
					else // 그림자 윗변이 오브젝트 윗변보다 위에 있을 경우
					{
						cha->pos.x = obj->bottomPlane[1].getStart().x + cha->size.x / 2;
					}

				}
			}
		}
		if (cha->prePos.z < cha->pos.z) // 플레이어가 아래로 움직였을 때
		{
			if (obj->bottomPlane[0].getStart().x < sh->RB.x &&
				sh->LB.x < obj->bottomPlane[0].getEnd().x) // 오브젝트의 x 범위 안에 들어왔을 때
			{
				if (sh->LT.z < obj->bottomPlane[0].getStart().z &&
					obj->bottomPlane[0].getStart().z < sh->LB.z) // 밑변이 오브젝트의 윗변을 넘어가면
				{
					cha->pos.z = obj->bottomPlane[0].getStart().z - 10;
				}
			}
			else if (obj->bottomPlane[3].getEnd().z < sh->RB.z &&
				sh->RT.z < obj->bottomPlane[3].getStart().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
			{
				if (Linear(sh->LB, sh->RB).segmentIntersect(obj->bottomPlane[3], &interVector) ||
					Linear(sh->LT, sh->RT).segmentIntersect(obj->bottomPlane[3], &interVector)) // 밑변 선분이 좌측변이랑 교차하면
				{
					if (interVector.x < sh->RB.x)
					{
						cha->pos.x = interVector.x - cha->size.x / 2; // 교차 점에서 왼쪽으로 보정
					}
				}
			}
		}
		else if (cha->pos.z < cha->prePos.z) // 플레이어가 위쪽으로 움직였을 때
		{
			if (obj->bottomPlane[2].getEnd().x < sh->RT.x &&
				sh->LT.x < obj->bottomPlane[2].getStart().x) // 오브젝트의 x 범위 안에 들어왔을 때
			{
				if (sh->RT.z < obj->bottomPlane[2].getEnd().z &&
					obj->bottomPlane[2].getEnd().z < sh->RB.z) // 윗변이 오브젝트의 밑면을 넘어가면
				{
					cha->pos.z = obj->bottomPlane[2].getEnd().z + 10;
				}
			}
			else if (obj->bottomPlane[3].getEnd().z < sh->RB.z &&
				sh->RT.z < obj->bottomPlane[3].getStart().z) // Object의 z 범위 안에 있을 때 (왼쪽 오른쪽)
			{
				if (Linear(sh->LT, sh->RT).segmentIntersect(obj->bottomPlane[1], &interVector) ||
					Linear(sh->LB, sh->RB).segmentIntersect(obj->bottomPlane[1], &interVector)) // 윗변 선분이 교차하면
				{
					if (sh->LT.x < interVector.x)
					{
						cha->pos.x = interVector.x + cha->size.x / 2; // 교차 점에서 오른쪽으로 보정
					}
				}
			}
		}
	}
}
void Player::AirCollision(GameObject* cha, tagShadow* sh, GameObject * obj)
{
	if (cha->prePos.y < cha->pos.y) // 낙하 중일 때
	{
		if (obj->bottomPlane[0].getStart().z < sh->LB.z &&			// 캐릭터의 z값이 윗변보다 밑에 있고
			sh->LT.z < obj->bottomPlane[2].getStart().z &&			// 캐릭터의 z값이 밑변보다 위에 있고
			obj->bottomPlane[3].getX(sh->RB.z) < sh->RB.x &&			// 캐릭터의 x값이 좌측변보다 우측에 있고
			sh->LB.x < obj->bottomPlane[1].getX(sh->LT.z))			// 캐릭터의 x값이 우측변보다 좌측에 있고
		{
			if (cha->prePos.y <= obj->topPlane[0].getStart().y)			// 이전 y값이 오브젝트 높이 값보다 크면
			{
				if (obj->topPlane[0].getStart().y < cha->pos.y)			// 오브젝트 위로 떨어지면
				{
					cha->pos.y = obj->topPlane[0].getStart().y;
					_info.jumpPower = 0;
					_info.isSky = false;
				}
			}
			else
			{
				LRUDCollision(cha, sh, obj);
			}
		}

	}
	else if (cha->pos.y < cha->prePos.y) // 점프 중일 때
	{
		if (obj->topPlane[0].getStart().y < cha->pos.y) // 오브젝트 높이보다 낮을 때
		{
			LRUDCollision(cha, sh, obj);
		}
	}
	else // 그냥 지면에 있을 때
	{
		LRUDCollision(cha, sh, obj);

	}
}







