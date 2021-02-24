#include "stdafx.h"
#include "playerDashAttack.h"

void playerDashAttack::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_dashAttack", true);
	
	//Ű���� �Ұ�
	_thisPl->setIsControl(false);

	//���⿡ ���� ���� ��Ʈ ����
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x - _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE* 0.2, ATTACKSIZE / 2);
		break;
	case DIRECTION::RIGHT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x + _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE*0.2, ATTACKSIZE / 2);
		break;
	}
	
	//���ݿ���
	if(checkEnemy())_isCollision = true;

	//���ⶳ��߸���
	dropWeapon();
}

void playerDashAttack::UpdateState()
{
	//�������� 1��
	_thisPl->getInfo().isAttack = false;
	
	//�ǰݿ� �����ߴٸ� �ε�����ȣ�� ���⿡ ���� Ư�� ��ȣ�϶� ����Ʈ�� �ѹ��� ���
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_isCollision && _thisPl->getObj().imgIndex.x >= 6)
		{
			SOUND_M->playSFX("kyoko_sAttack");

			EFFECT_M->play("ef_blueAttack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isCollision = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 6)
		{
			EFFECT_M->play("ef_blueAttack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isCollision = false;
		}
		break;
	}

	//�������� �� ���� ���� ���·� ���ư���
	if (isEndFrame(true)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	if (isEndFrame(true)
		&& !KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	//�޸��� Ű�� ������ ������ �޸��� ���·� ���ư���
	if (isEndFrame(true)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

	if (isEndFrame(true)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}
	//�̵�
	if (_thisPl->getInfo().dest == DIRECTION::LEFT)
		_thisPl->movePos(-_thisPl->getInfo().speed*1.2, 0, 0);

	if (_thisPl->getInfo().dest == DIRECTION::RIGHT)
		_thisPl->movePos(_thisPl->getInfo().speed*1.2, 0, 0);
}

void playerDashAttack::ExitState()
{
}
