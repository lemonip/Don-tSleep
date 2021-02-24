#include "stdafx.h"
#include "playerRun.h"

void playerRun::EnterState()
{
	//�̹��� ����
	if (_thisPl->getInfo().hasWeapon)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatRun", true);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}
	}
	else _thisPl->changeImg("pl_run", true);

	//���⿡ ���� ����Ʈ ����
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		EFFECT_M->play("ef_runL", _thisPl->getObj().rc.right, _thisPl->getObj().rc.bottom);
		break;
	case DIRECTION::RIGHT:
		EFFECT_M->play("ef_runR", _thisPl->getObj().rc.left,_thisPl->getObj().rc.bottom);
		break;
	}



	//Ű���� ����
	_thisPl->setIsControl(true);
	//������ȯ ����
	_thisPl->getInfo().isConDest = true;
}

void playerRun::UpdateState()
{
	//Ű�� �� ������ �⺻����
	if (!KEY_M->isStayKeyDown(VK_LEFT)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& !KEY_M->isStayKeyDown(VK_UP)
		&& !KEY_M->isStayKeyDown(VK_DOWN))
		_thisPl->setState(PL_STATE::IDLE);

	//�̵�
	lineMove(_thisPl->getInfo().speed / 1.5);
	crossMove(_thisPl->getInfo().speed*1.5);

	//�����
	if (KEY_M->isOnceKeyDownV('S'))_thisPl->setState(PL_STATE::DASHATTACK);

	//������
	if (KEY_M->isOnceKeyDownV('D'))_thisPl->setState(PL_STATE::DASHSATTACK);


}

void playerRun::ExitState()
{
}
