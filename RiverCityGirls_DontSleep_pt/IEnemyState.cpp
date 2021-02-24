#include "stdafx.h"
#include "IEnemyState.h"

void IEnemyState::Jump()
{
	//�÷��̾ ������ ���� �ְ� ������ �ƴϸ� ������ �Ѵ�.
	if (_thisEn->getPlayerAddress()->getObj().pos.y < _thisEn->getObj()->pos.y && !_thisEn->getPlayerAddress()->getInfo().isSky)
	{
		if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			_thisEn->SetState(EN_STATE::EN_JUMP);
		}
	}
}

void IEnemyState::LookAtPlayer()
{
	//�÷��̾ �����ʿ� ������ ������ ������ ����. �ݴ�� ������ ����.
	if (_thisEn->getPlayerAddress()->getObj().pos.x > _thisEn->getObj()->pos.x) _thisEn->getInfo().dest = DIRECTION::RIGHT;
	else if (_thisEn->getPlayerAddress()->getObj().pos.x < _thisEn->getObj()->pos.x) _thisEn->getInfo().dest = DIRECTION::LEFT;
}

void IEnemyState::Attack()
{
	//���� ��Ʈ ũ��� ��ġ ����
	
	
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT)
	{
		if (_thisEn->getObj()->imgIndex.x == 3) 
		{
			_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.right, _thisEn->getObj()->rc.top, 100, 200);
			_thisEn->getInfo().isAttack = true;
		}
		
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT)
	{
		if (_thisEn->getObj()->imgIndex.x == 3)
		{
			_thisEn->getInfo().rcAttack = RectMake(_thisEn->getObj()->rc.left - 100, _thisEn->getObj()->rc.top, 100, 200);
			_thisEn->getInfo().isAttack = true;
		}
		
	}
		
	
}

bool IEnemyState::endFrame()
{
	if (_thisEn->getInfo().dest == DIRECTION::RIGHT && _thisEn->getObj()->imgIndex.x >= _thisEn->getObj()->img->getMaxFrameX())
	{
		return true;
	}
	else if (_thisEn->getInfo().dest == DIRECTION::LEFT && _thisEn->getObj()->imgIndex.x <= 0)
	{
		return true;
	}
	return false;
}

void IEnemyState::Damage(int atk)
{
	_thisEn->getInfo().hp -= atk;
	//cout << _thisEn->getInfo().hp << endl;

	if (_thisEn->getInfo().hp < 0) { _thisEn->getInfo().hp = 0; }

	//ü���� 0�̸� �״´�.
	if (_thisEn->getInfo().hp == 0) { _thisEn->SetState(EN_STATE::EN_DIE); }
	//ü���� 1/3 ���ϸ� ����
	else if (_thisEn->getInfo().hp <= _thisEn->getInfo().maxHp / 3)
	{ 
		if(RND->getInt(10) <= 10)
		_thisEn->SetState(EN_STATE::EN_BEGGING);
	}
	//ü���� 1/2 ���ϸ� ����
	else if (_thisEn->getInfo().hp <= _thisEn->getInfo().maxHp / 2)
	{ 
		if (RND->getInt(10) <= 10)
		_thisEn->SetState(EN_STATE::EN_STUN);
	}
}
