#include "stdafx.h"
#include "playerJumpAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerJumpAttack::EnterState()
{
	//방향 변경 불가
	_thisPl->getInfo().isConDest = false;

	//이미지 변경 불가
	_thisPl->changeImg("pl_jumpAttack",false);

	//충돌 변수초기화
	_isCollision = false;
	_isEffect = false;

	//무기를 들고 있다면 떨어뜨리기
	if (_thisPl->getInfo().hasWeapon)
	{
		//무기를 떨어뜨림.
		_thisPl->getInfo().hasWeapon = false;
		//무기의 떨어질 초기위치 설정
		_thisPl->getInfo().attackObj->pos.x = _thisPl->getObj().pos.x;
		_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y;
		_thisPl->getInfo().attackObj->pos.z = _thisPl->getObj().pos.z;

		//무기 렌더 활성화
		_thisPl->getInfo().attackObj->isRender = true;

		//무기가 향할 골 설정
		_thisPl->getInfo().attackGoal.x = _thisPl->getObj().pos.x;
		if (_thisPl->getInfo().attackGoal.x > CAMERA_M->GetMapXSize())_thisPl->getInfo().attackGoal.x = CAMERA_M->GetMapXSize();
		_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y - 100;
		_thisPl->getInfo().attackGoal.z = _thisPl->getObj().pos.z;
		_thisPl->getInfo().attackGoal.y = _thisPl->getObj().pos.y - 100;
		_thisPl->getInfo().goalState = GOALPOS::WINOUT;
	}

}

void playerJumpAttack::UpdateState()
{
	RECT _temp;
	
	//방향에 따른 공격 렉트 생성
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x - _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE* 0.2, ATTACKSIZE );
		break;
	case DIRECTION::RIGHT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x + _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE*0.2, ATTACKSIZE );
		break;
	}
	
	//공격여부
	if (!_isCollision && checkEnemy())
	{
		_isCollision = true;
		_isEffect = true;
	
	}

	if (_isEffect)
	{
		//피격에 성공했다면 인덱스번호가 방향에 따라 특정 번호일때 이펙트를 한번만 출력하려다가 인덱스 번호 없는게 자연스러운것같음
		switch (_thisPl->getInfo().dest)
		{
		case DIRECTION::LEFT:
			//if( _thisPl->getObj().imgIndex.x >= 4)
			{
			EFFECT_M->play("ef_star", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom)*0.6);
			_isEffect = false;
			}
			break;
		case DIRECTION::RIGHT:
			//if(_thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 4)
			{
			EFFECT_M->play("ef_star", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom)*0.6);
			_isEffect = false;
			}
			break;
		}
	}
	//이동
	crossMove(_thisPl->getInfo().speed*1.2);
	lineMove(_thisPl->getInfo().speed / 2);

}

void playerJumpAttack::ExitState()
{
}
