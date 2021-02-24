#include "stdafx.h"
#include "playerDead.h"


void playerDead::EnterState()
{
	//���ⶳ��߸���
	dropWeapon();

	//�Ѿ����־����� �ٷ� �����̹����� ����
	if (_thisPl->getInfo().preState == PL_STATE::DOWN)
	_thisPl->changeImg("pl_dead", false);

	//���
	_thisPl->getInfo().isDead = true;

	//Ű���� �Ұ�
	_thisPl->setIsControl(false);

	//���İ�����
	_thisPl->getRefObj().alpha = 255;

	//�ð��� �ʱ�ȭ
	_stateTimer = TIME_M->getWorldTime();
}

void playerDead::UpdateState()
{
	if (TIME_M->getWorldTime() - _stateTimer > 4.f && _thisPl->getInfo().preState == PL_STATE::DOWN)
	{
		if (_thisPl->getStageM()->getCurStage() == STAGETYPE::BOSS)
		{
			UI_M->popUI("bossHPBar1");
			UI_M->popUI("bossHPBar2");
		}
		EVENT_M->addEvent(new heart(true));
		DATA_M->loadStageData();
		_thisPl->getInfo().isDead = false;
		_thisPl->setIsControl(true);
	}

	//�Ѿ������� �ʾҴٸ� �Ѿ�߸�
	if (_thisPl->getInfo().preState != PL_STATE::DOWN )
		_thisPl->setState(PL_STATE::DOWN);

	//�������°� �������� �ٵ��� ����� �� ���� ����
	if (isEndFrame(false) && _thisPl->getInfo().isDead && !_thisPl->getInfo().isRestart)_thisPl->getInfo().isRestart = true;

}

void playerDead::ExitState()
{

}
