#include "stdafx.h"
#include "IPlayerState.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "ObjectManager.h"
#include "Object.h"
#include "Weapon.h"

//������Ʈ �Ͻ����� ���� 
bool IPlayerState::pauseUpdate()
{
	//Ű������ �Ұ����ϰ�� 
	if (!_thisPl->getInfo().isControl) return true;

	//�׿�
	else return false;
}

//������ ���࿩��
bool IPlayerState::isEndFrame(bool reverse)
{
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
	{
		//���� �����ӹ�ȣ�� ����ȣ�� ����������� ��
		if (reverse == false && _thisPl->getObj().img->getFrameX() >= _thisPl->getObj().img->getMaxFrameX())
			return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() <= 0)
			return true;

		return false;
	}
	case DIRECTION::RIGHT:
	{
		//���� �����ӹ�ȣ�� 0 ��ȣ�� ����������� ��
		if (reverse == false && _thisPl->getObj().img->getFrameX() <= 0) return true;
		if (reverse == true && _thisPl->getObj().img->getFrameX() >= _thisPl->getObj().img->getMaxFrameX())return true;
		return false;
	}
	}
}

//���� ����߸���
void IPlayerState::dropWeapon()
{
	//���⸦ ��� �ִٸ� ����߸���
	if (_thisPl->getInfo().hasWeapon)
	{
		//���⸦ ����߸�.
		_thisPl->getInfo().hasWeapon = false;
		//������ ������ �ʱ���ġ ����
		_thisPl->getInfo().attackObj->pos.x = _thisPl->getObj().pos.x;
		_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y;
		_thisPl->getInfo().attackObj->pos.z = _thisPl->getObj().pos.z;

		//���� ���� Ȱ��ȭ
		_thisPl->getInfo().attackObj->isRender = true;

		//���Ⱑ ���� �� ����
		_thisPl->getInfo().attackGoal.x = _thisPl->getObj().pos.x;
		if (_thisPl->getInfo().attackGoal.x > CAMERA_M->GetMapXSize())_thisPl->getInfo().attackGoal.x = CAMERA_M->GetMapXSize();
		_thisPl->getInfo().attackObj->pos.y = _thisPl->getObj().pos.y - 100;
		_thisPl->getInfo().attackGoal.z = _thisPl->getObj().pos.z;
		_thisPl->getInfo().attackGoal.y = _thisPl->getObj().pos.y - 100;
		_thisPl->getInfo().goalState = GOALPOS::WINOUT;
	}

}

void IPlayerState::walkPattern()
{
	//�ȱ�
	if (KEY_M->isStayKeyDown(VK_LEFT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_RIGHT))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_UP))_thisPl->setState(PL_STATE::WALK);
	if (KEY_M->isStayKeyDown(VK_DOWN))_thisPl->setState(PL_STATE::WALK);
}

void IPlayerState::basePattern()
{
	//�ȱ�
	walkPattern();

	//����
	if (KEY_M->isStayKeyDown('F'))_thisPl->setState(PL_STATE::GUARD);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::COMBO1);

}

bool IPlayerState::checkWeapon()
{
	RECT temp;
	for (int i = 0; i != _thisPl->getObjectM()->getVObject().size(); i++)
	{
		if (_thisPl->getObjectM()->getVObject()[i]->getObj()->group != OBJECT_GROUP::WEAPON) continue;

		if (!_thisPl->getObjectM()->getVObject()[i]->getObj()->isRender) continue;

		if (IntersectRect(&temp, &_thisPl->getRefObj().rc,
			&(_thisPl->getObjectM()->getVObject()[i]->getObj()->rc))
			&& _thisPl->isRange(*_thisPl->getObjectM()->getVObject()[i]->getObj()))
		{
			_thisPl->getObjectM()->popObject(i);
			Object* weapon = new Weapon(WEAPON_TYPE::BAT, vector3(0,0,0));
			_thisPl->getInfo().attackObj = weapon->getObj();
			_thisPl->getInfo().attackObj->isRender = false;
			return true;
		}
	}
	return false;
}

//���ݻ��¸� �������� ��ȯ
bool IPlayerState::checkEnemy()
{
	RECT temp;
	//���ͼ�Ʈ��Ʈ�� / isrange�Լ��� ���� ��. ����� ������ z�����ִ��� Ȯ����.
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		if (_thisPl->getEnemyM()->getVEnemy()[i]->getInfo().isAttack)return false;

		if (IntersectRect(&temp, &_thisPl->getInfo().attackRc,
			&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
			&& _thisPl->isRange(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj()))
		{
			_thisPl->getInfo().isAttack = true;
			return _thisPl->getInfo().isAttack;
		}
	}
	return false;
}

//������
void IPlayerState::sAttack()
{
	if (KEY_M->isOnceKeyDownV('D')) _thisPl->setState(PL_STATE::SATTACK);
	//_thisPl->setState(PL_STATE::HIT);
	{
		//for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
		//{
		//	//if (_thisPl->getEnemyM()->getVEnemy()[i]);
		//	_thisPl->setState(PL_STATE::SATTACK);
		//	//�� �����°� ���������¸� �������� ���۹ٲٱ�
		//	//if (_thisPl->getEnemyM()->getVEnemy()[i]);
		//}
	}
}

//�����̵�
void IPlayerState::lineMove(float speed)
{	
	if (KEY_M->isStayKeyDown(VK_UP))
		_thisPl->movePos(0, -speed, 0);

	if (KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->movePos(0, speed, 0);
}

//�¿��̵�
void IPlayerState::crossMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_RIGHT))
		_thisPl->movePos(speed, 0, 0);

	if (KEY_M->isStayKeyDown(VK_LEFT))
		_thisPl->movePos(-speed, 0, 0);
}

void IPlayerState::ladderMove(float speed)
{
	if (KEY_M->isStayKeyDown(VK_UP))
	{
		_thisPl->movePos(0, 0, speed);
	}


	if (KEY_M->isStayKeyDown(VK_DOWN))
	{
		_thisPl->movePos(0, 0, -speed);
	}
}
