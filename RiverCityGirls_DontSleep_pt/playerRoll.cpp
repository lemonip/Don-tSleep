#include "stdafx.h"
#include "playerRoll.h"

void playerRoll::EnterState()
{
	//�̹�������
	_thisPl->changeImg("pl_roll",false);
	//Ű���� �Ұ��� ����
	_thisPl->setIsControl(false);

	//�̹û���
	_thisPl->getInfo().isImmune = true;
}

void playerRoll::UpdateState()
{
	//�̵�
	if (_thisPl->getInfo().dest == DIRECTION::LEFT)
		_thisPl->movePos(-_thisPl->getInfo().speed*2.5, 0, 0);
	if (_thisPl->getInfo().dest == DIRECTION::RIGHT)
		_thisPl->movePos(_thisPl->getInfo().speed*2.5, 0, 0);
	
	//�̹û��� + ���İ� ����
	_thisPl->getPObj()->alpha = 160;
	
	//�������� ������ Ű���� ���
	if (isEndFrame(false))
	{
		_thisPl->setIsControl(true);
		_thisPl->getInfo().isImmune = false;
		_thisPl->getPObj()->alpha = 255;
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerRoll::ExitState()
{
}
