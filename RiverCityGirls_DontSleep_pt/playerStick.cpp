#include "stdafx.h"
#include "playerStick.h"

void playerStick::EnterState()
{
	//�̹�������
	_thisPl->changeImg("pl_stick", false);
	_stateTimer = TIME_M->getWorldTime();
	//Ű���ۺҰ�
	_thisPl->setIsControl(false);
}

void playerStick::UpdateState()
{
	//�ð��� ������ �������� ��������
	if (TIME_M->getWorldTime() - _stateTimer > 1.5f)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	//����
	if (KEY_M->isOnceKeyDownV('A'))
	{
		_thisPl->setIsSky(true);
		_thisPl->setIsControl(true);
		_thisPl->movePos(0, 0, JUMPPOWER);
		_thisPl->setJumpPower(JUMPPOWER);
		_thisPl->setState(PL_STATE::JUMP);
	}
}

void playerStick::ExitState()
{
}
