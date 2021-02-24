#include "stdafx.h"
#include "playerSAttackDown.h"

void playerSAttackDown::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_sAttackDown", true);	

	//Ű�Է� ����
	_thisPl->setIsControl(false);

	//���⿡ ���� ���� ��Ʈ ����
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x - _thisPl->getObj().size.x /6 ,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE* 0.8, ATTACKSIZE / 2);
		break;
	case DIRECTION::RIGHT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x + _thisPl->getObj().size.x / 6,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE*0.8, ATTACKSIZE / 2);
		break;
	}

	//���ⶳ��߸���
	dropWeapon();
	SOUND_M->playSFX("kyoko_hurricane");


}

void playerSAttackDown::UpdateState()
{
	//���ݿ��� üũ
	checkEnemy();

	if (isEndFrame(true))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttackDown::ExitState()
{
}
