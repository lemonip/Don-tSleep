#include "stdafx.h"
#include "playerIdle.h"
#include "Enemy.h"
#include "EnemyManager.h"

void playerIdle::EnterState()
{
	//�̹��� ����
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatIdle", true);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}

	}
	else _thisPl->changeImg("pl_idle", true);

	//���������� ������ ���·� ����
	_thisPl->getInfo().isConDest = true;
	//���� ���� �ƴ�
	_thisPl->getInfo().isAttack = false;
	//Ÿ�̸Ӹ� ����Ÿ�̸ӷ� ���缭 �ʱ�ȭ
	_stateTimer = TIME_M->getWorldTime();

	//ŰĿ�Ǵ� ���� ���
	KEY_M->clearVKey();

	//�����������·κ���
	
}

void playerIdle::UpdateState()
{
	//�����ð����� �������� ������ ��ٸ� ���·� ��ȯ
	if (TIME_M->getWorldTime() - _stateTimer > 3.0f)_thisPl->setState(PL_STATE::WAIT);
	//������Ʈ ���� ����
	if (pauseUpdate())return;

	//�⺻ ����
	basePattern();
	
	//������
	sAttack();

	//�ݱ�
	if (KEY_M->isOnceKeyDownV('E')) { _thisPl->setState(PL_STATE::PICK); }
	
	//����Ǳ�

	RECT temp;
	//���ͼ�Ʈ��Ʈ�� / isrange�Լ��� ���� ��. ����� ������ z�����ִ��� Ȯ����.

	//���ᰡ ���� ���¿��� �����ִ� ���ʹ̶� �浹�ϸ�
	if(!_thisPl->getInfo().hasMember)
	{
		for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
		{
			if(_thisPl->getEnemyM()->getVEnemy()[i]->getState() ==EN_STATE::EN_BEGGING)
			{
				if (IntersectRect(&temp, &_thisPl->getRefObj().rc,
					&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc))
					&& _thisPl->isRange(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj()))
				{
					_thisPl->setState(PL_STATE::GRAB);
				}
			}
		}
	}
	if (KEY_M->isOnceKeyDownV('Q')) 
	{
		_thisPl->setState(PL_STATE::PICK); 
	}

}

void playerIdle::ExitState()
{
}
