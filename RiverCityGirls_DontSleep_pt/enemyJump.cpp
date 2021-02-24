#include "stdafx.h"
#include "enemyJump.h"
#include "Enemy.h"

void enemyJump::EnterState()
{
	SOUND_M->playSFX("enemy_jump");
	_thisEn->SetImage();
	_thisEn->getInfo().jumpPower = JUMPPOWER;
	_thisEn->getInfo().isSky = true;
}

void enemyJump::UpdateState()
{
	//å�� � �÷��̾ �ö󰬴µ� �� �ڸ����� ������ �ϸ� �� �ǹǷ� �̵����� �ش�.
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x >= _thisEn->getObj()->img->getMaxFrameX())
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed, 0);
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x <= 0)
	{
		_thisEn->xzyMove(cosf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed,
			-sinf(getAngle(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z)) * _thisEn->getInfo().speed, 0);
	}
	
	if (_thisEn->getObj()->pos.y > 0)
	{
		_thisEn->getObj()->pos.y = 0;
	}
	if (_thisEn->getObj()->pos.y == 0)
	{
		_thisEn->SetState(EN_STATE::EN_WALK);
	}
	//�÷��̾ �ٴڿ� ������ ���� ������ �Ѵ�.
	if (_thisEn->getPlayerAddress()->getObj().pos.y == 0 && !_thisEn->getPlayerAddress()->getInfo().isSky
		&& _thisEn->getInfo().jumpPower <= JUMPPOWER/3*2)
	{
		_thisEn->SetState(EN_STATE::EN_JUMPATTACK);
	}
}

void enemyJump::ExitState()
{
	_thisEn->getInfo().jumpPower = 0;
}

