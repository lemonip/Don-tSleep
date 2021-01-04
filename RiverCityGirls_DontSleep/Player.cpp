#include "stdafx.h"
#include "Player.h"

#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"

HRESULT Player::init()
{
	/*====================================================================
		플래이어의 오브젝트 초기화와 기본 설정을 합니다.
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("kyoko"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2));
	_obj.imgIndex = { 0,0 };	//아직 애니메이션이 만들어지지 않아 임시로 해두었습니다.

	_speed = SPEED;
	_jumpCount = 1;
	_isControl = true;

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

void Player::update()
{
	keyInput();
	move();
	shadowUpdate();
	_obj.update();
	playerObjectCollision();
	shadowUpdate();
	_obj.update();
}

void Player::render()
{
	/*====================================================================
		Z-ORDER에 따라 알파 프레임 렌더 시킵니다.
	====================================================================*/
	ZORDER_M->renderObject(getMapDC(), &_obj, RENDERTYPE::FRAME_RENDER);
	//(아직 플래이어 애니메이션이 없어 임시로 해두었습니다. 나중에 ANI_RENDER로 바꿔서 쓰세요!)
}

void Player::move()
{
	_obj.prePos = _obj.pos;
	_obj.pos.y -= _jumpPower;
	if (_obj.pos.y > _jumpPower)_jumpPower = 0;
	if (_obj.pos.y < 0) _jumpPower -= GRAVITY;

	if (_jumpPower == 0) _jumpCount = 1;
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

void Player::keyInput()
{
	if (!_isControl) return;		//컨트롤이 불가능하면 리턴한다.

	if (KEY_M->isOnceKeyDown(VK_SPACE) && _jumpPower <= 0 && _jumpCount > 0)
	{
		_jumpPower = JUMPPOWER;
		_jumpCount--;
	}

	if (KEY_M->isStayKeyDown(VK_UP))
	{
		_obj.pos.z -= _speed;
	}
	if (KEY_M->isStayKeyDown(VK_DOWN))
	{
		_obj.pos.z += _speed;
	}

	if (KEY_M->isStayKeyDown(VK_RIGHT))
	{
		_obj.pos.x += _speed;
	}

	if (KEY_M->isStayKeyDown(VK_LEFT))
	{
		_obj.pos.x -= _speed;
	}
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
					_jumpPower = 0;
					_jumpCount = 0;
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
