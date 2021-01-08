#include "stdafx.h"
#include "IPlayerState.h"
#include "EnemyManager.h"
#include "Enemy.h"

//업데이트 일시정지 유무 
bool IPlayerState::pauseUpdate()
{
	//키조작이 불가능일경우 
	if (!_thisPl->getInfo().isControl) return true;

	//그외
	else return false;
}

//프레임 실행여부
bool IPlayerState::isEndFrame(bool reverse)
{
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
	{
		//현재 프레임번호가 끝번호면 프레임재생이 끝
		if (reverse == false && _thisPl->getObj().img->getFrameX() >= _thisPl->getObj().img->getMaxFrameX())
			return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() <= 0)
			return true;

		return false;
	}
	case DIRECTION::RIGHT:
	{
		//현재 프레임번호가 0 번호면 프레임재생이 끝
		if (reverse == false && _thisPl->getObj().img->getFrameX() <= 0) return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() >= _thisPl->getObj().img->getMaxFrameX())return true;
		return false;
	}
	}
}

void IPlayerState::walkPattern()
{
	//걷기
	if (KEY_M->isStayKeyDown(VK_LEFT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_RIGHT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_UP))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_DOWN))_thisPl->setState(PL_STATE::WALK);
}

void IPlayerState::basePattern()
{
	//걷기
	walkPattern();

	//가드
	if (KEY_M->isStayKeyDown('F'))_thisPl->setState(PL_STATE::GUARD);

	//약공격
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO1);

}

//공격상태면 공격으로 전환
void IPlayerState::checkAttack()
{
	RECT temp;
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (IntersectRect(&temp, &_thisPl->getInfo().attackInfo._obj.rc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
			&& _thisPl->isRange(*_thisPl->getEnemyM()->getVEnemy()[i]->getObj()))
			_thisPl->SetIsAttack(true);
	}
}

//강공격
void IPlayerState::sAttack()
{
	if (KEY_M->isOnceKeyDownV('D'))
	{
		for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
		{
			//if (_thisPl->getEnemyM()->getVEnemy()[i]);
			_thisPl->setState(PL_STATE::SATTACK);
			//★ 적상태가 쓰러진상태면 스톰프로 동작바꾸기
			//if (_thisPl->getEnemyM()->getVEnemy()[i]);
		}
	}
}

//상하이동
void IPlayerState::lineMove(float speed)
{	
	if (KEY_M->isStayKeyDown(VK_UP))
		_thisPl->movePos(0, -speed, 0);

	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->movePos(0, speed, 0);
}

//좌우이동
void IPlayerState::crossMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->movePos(speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->movePos(-speed, 0, 0);
}
