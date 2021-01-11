#include "stdafx.h"
#include "enemyHit.h"
#include "Enemy.h"


void enemyHit::EnterState()
{
	_thisEn->SetImage();
	Damage(_thisEn->getPlayerAddress()->getInfo().force);
	if (_thisEn->getPlayerAddress()->getInfo().state == PL_STATE::COMBO3) isDown = true;
}

void enemyHit::UpdateState()
{
	LookAtPlayer();
	if (_thisEn->getPlayerAddress()->getInfo().state == PL_STATE::COMBO1)
	{
		cout << "check1" << endl;
		if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
		{
			//_thisEn->getObj()->imgIndex.x = 0;
			if (_thisEn->getObj()->imgIndex.x >= 2)
			{
				_thisEn->getObj()->imgIndex.x = 0;
			}
		}
		if (_thisEn->getInfo().dest == DIRECTION::LEFT)
		{
			//_thisEn->getObj()->imgIndex.x = _thisEn->getObj()->img->getMaxFrameX();
			if (_thisEn->getObj()->imgIndex.x <= 6)
			{
				_thisEn->getObj()->imgIndex.x = _thisEn->getObj()->img->getMaxFrameX();
			}
		}
	}
	if (_thisEn->getPlayerAddress()->getInfo().state == PL_STATE::COMBO2)
	{
		cout << "check2" << endl;
		if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisEn->getObj()->imgIndex.x = 3;
			if (_thisEn->getObj()->imgIndex.x > 5)
			{
				_thisEn->getObj()->imgIndex.x = 3;
			}
		}
		if (_thisEn->getInfo().dest == DIRECTION::LEFT)
		{
			_thisEn->getObj()->imgIndex.x = 5;
			if (_thisEn->getObj()->imgIndex.x < 3)
			{
				_thisEn->getObj()->imgIndex.x = 5;
			}
		}
	}
	if (_thisEn->getPlayerAddress()->getInfo().state == PL_STATE::COMBO3)
	{
		cout << "check3" << endl;
		if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisEn->getObj()->imgIndex.x = 6;
			if (_thisEn->getObj()->imgIndex.x > _thisEn->getObj()->img->getMaxFrameX())
			{
				_thisEn->getObj()->imgIndex.x = 6;
			}
		}
		if (_thisEn->getInfo().dest == DIRECTION::LEFT)
		{
			_thisEn->getObj()->imgIndex.x = 2;
			if (_thisEn->getObj()->imgIndex.x < 0)
			{
				_thisEn->getObj()->imgIndex.x = 2;
			}
		}
	}
	//HIT의 상태가 끝났다.
	if (endFrame())
	{
		if (isDown) _thisEn->SetState(EN_STATE::EN_DOWN);
		else _thisEn->SetState(EN_STATE::EN_IDLE);
	}
}

void enemyHit::ExitState()
{
	isDown = false;
}
