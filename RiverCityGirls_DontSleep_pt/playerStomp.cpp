#include "stdafx.h"
#include "playerStomp.h"

void playerStomp::EnterState()
{
	//�����ʱ�ȭ
	_isCollision = false;

	//�̹��� ����
	_thisPl->changeImg("pl_stomp", true);

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

	//���ݿ��� üũ
	if (checkEnemy())_isCollision = true;

	//���ⶳ��߸���
	dropWeapon();
}

void playerStomp::UpdateState()
{
	//����������
	_thisPl->getInfo().isAttack = false;

	//�ǰݿ� �����ߴٸ� �ε�����ȣ�� ���⿡ ���� Ư�� ��ȣ�϶� ����Ʈ�� �ѹ��� ���
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 6)
		{
			SOUND_M->playSFX("kyoko_stomp");

			EFFECT_M->play("ef_spark", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) *0.6);
			_isCollision = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_isCollision && _thisPl->getObj().imgIndex.x >= 6)
		{
			
			SOUND_M->playSFX("kyoko_stomp");

			EFFECT_M->play("ef_spark", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom)*0.6);
			_isCollision = false;
		}
		break;
	}
	
	//�������� �� ���� ���� ���·� ���ư���
	if (isEndFrame(true))
	{
		_thisPl->setIsControl(true);
		_thisPl->setState(PL_STATE::IDLE);
	}

}

void playerStomp::ExitState()
{
}
