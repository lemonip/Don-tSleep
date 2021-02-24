#include "stdafx.h"
#include "playerStun.h"

void playerStun::EnterState()
{
	//�̹�������
	_thisPl->changeImg("pl_stun", true);
	//Ű���ۺҰ�
	_thisPl->setIsControl(false);

	//���ķ��� ����
	_thisPl->getRefObj().alpha = 255;

	//����Ʈ ���
	EFFECT_M->play("ef_stun", (_thisPl->getObj().rc.left + _thisPl->getObj().rc.right) /2, _thisPl->getObj().rc.top);

	//���� Ÿ�̸� �ʱ�ȭ
	_stateTimer = TIME_M->getWorldTime();

	//�̹û��·� �����
	_thisPl->getInfo().isImmune = true;


}

void playerStun::UpdateState()
{
	if (TIME_M->getWorldTime()- _stateTimer >1.5f)
	{
		_thisPl->getRefObj().alpha = 180;
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerStun::ExitState()
{
	_thisPl->setIsControl(true);

}
