#include "stdafx.h"
#include "playerWait.h"

void playerWait::EnterState()
{
	_thisPl->changeImg("pl_wait",false);
}

void playerWait::UpdateState()
{
	//�������� �������� �Ϲ� ���·� ��ȯ
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);
	
	//������Ʈ ���� ����
	if (pauseUpdate())return;
	
	//�⺻����
	basePattern();

	//������
	sAttack();

}

void playerWait::ExitState()
{
}
