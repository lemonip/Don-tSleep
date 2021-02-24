#include "stdafx.h"
#include "playerPick.h"

void playerPick::EnterState()
{
	if (!checkWeapon()) { _thisPl->setState(PL_STATE::IDLE); return; }

	_thisPl->getInfo().attackObj->isRender = false;

	//�̹�������
	_thisPl->changeImg("pl_pick", false);
	//���⸦ �����ٰ� ��
	_thisPl->getInfo().hasWeapon = true;
}

void playerPick::UpdateState()
{
	if (isEndFrame(false))
	{
		_thisPl->setState(PL_STATE::IDLE);
		_thisPl->getInfo().hasWeapon = true;
	}
}

void playerPick::ExitState()
{
}
