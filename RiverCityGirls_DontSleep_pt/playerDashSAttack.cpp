#include "stdafx.h"
#include "playerDashSAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerDashSAttack::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_dashSAttack", false);

	//Ű���� �Ұ�
	_thisPl->setIsControl(false);

	//�浹 �����ʱ�ȭ
	_isCollision = false;

	//���ⶳ��߸���
	dropWeapon();
}

void playerDashSAttack::UpdateState()
{
	RECT _temp;

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
	if (!_isCollision && checkEnemy())
	{
		_isCollision = true;
		//�ǰݿ� �����ߴٸ� �ε�����ȣ�� ���⿡ ���� Ư�� ��ȣ�϶� ����Ʈ�� �ѹ��� ���
		switch (_thisPl->getInfo().dest)
		{
		case DIRECTION::LEFT:
			SOUND_M->playSFX("kyoko_dashSAttack");

				EFFECT_M->play("ef_blueAttack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
					(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			break;
		case DIRECTION::RIGHT:
			SOUND_M->playSFX("kyoko_dashSAttack");

				EFFECT_M->play("ef_blueAttack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
					(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			break;
		}
	}
	
	//�������� �� ���� ���� ���·� ���ư���
	if (isEndFrame(false)
		&& !KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

	if (isEndFrame(false)
		&& !KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}
	
	//�޸��� Ű�� ������ ������ �޸��� ���·� ���ư���
	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_RIGHT)
		&& _thisPl->getInfo().dest == DIRECTION::RIGHT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}

	if (isEndFrame(false)
		&& KEY_M->isStayKeyDown(VK_LEFT)
		&& _thisPl->getInfo().dest == DIRECTION::LEFT)
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::RUN);
	}
	

	//�̵�
	if (_thisPl->getInfo().dest == DIRECTION::LEFT
		&&_thisPl->getObj().img->getFrameX() <= _thisPl->getObj().img->getMaxFrameX()-10)
		_thisPl->movePos(-_thisPl->getInfo().speed*1.7, 0, 0);

	if (_thisPl->getInfo().dest == DIRECTION::RIGHT
		&&_thisPl->getObj().img->getFrameX() >= 10)
		_thisPl->movePos(_thisPl->getInfo().speed*1.7, 0, 0);


}

void playerDashSAttack::ExitState()
{
	
}
