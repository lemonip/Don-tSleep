#include "stdafx.h"
#include "playerWalk.h"

void playerWalk::EnterState()
{
	//�̹��� ����
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
			case WEAPON_TYPE::BAT:
				_thisPl->changeImg("pl_wBatWalk", true);
			break;
			case WEAPON_TYPE::BASEBALL:
				//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}
	}
	else _thisPl->changeImg("pl_walk", true);
	
	_stateTimer = TIME_M->getWorldTime();
	//���⺯�氡�ɻ��·� ��ȯ
	_thisPl->getInfo().isConDest = true;
	//Ű���� ����
	_thisPl->setIsControl(true);
}

void playerWalk::UpdateState()
{
	//�ѹ��� ������ �뽬
	if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::LEFT &&
		KEY_M->isOnceKeyDownV(VK_LEFT))_thisPl->setState(PL_STATE::RUN);

	if (_thisPl->getInfo().moveDest == MOVE_DIRECTION::RIGHT &&
		KEY_M->isOnceKeyDownV(VK_RIGHT))_thisPl->setState(PL_STATE::RUN);

	//0.25�ʾȿ� Ű�� ������ ������ �⺻ ����
	if (TIME_M->getWorldTime() - _stateTimer >0.25f
		&&!KEY_M->isStayKeyDown(VK_LEFT)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& !KEY_M->isStayKeyDown(VK_UP)
		&& !KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->setState(PL_STATE::IDLE);

	//�̵�
	lineMove(_thisPl->getInfo().speed / 2);
	crossMove(_thisPl->getInfo().speed);
}

void playerWalk::ExitState()
{
}
