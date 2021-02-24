#include "stdafx.h"
#include "playerHit.h"
#include "EnemyManager.h"
#include "Enemy.h"


void playerHit::EnterState()
{
	RECT temp;

	SOUND_M->playSFX("kyoko_hit");

	//�̹û��·� �����
	_thisPl->getInfo().isImmune = true;
	_thisPl->getRefObj().alpha = 180;

	//������ ����
	_thisPl->getInfo().hitCount++;

	//�̹�������
	_thisPl->changeImg("pl_hit", false);

	//Ű���ۺҰ�
	_thisPl->setIsControl(false);

	

	//���ⶳ��߸���
	dropWeapon();
}

void playerHit::UpdateState()
{

	//�������� ������ Ű���� ���
	if (isEndFrame(false))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerHit::ExitState()
{
	_thisPl->setIsControl(true);

}
