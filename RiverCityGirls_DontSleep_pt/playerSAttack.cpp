#include "stdafx.h"
#include "playerSAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerSAttack::EnterState()
{
	RECT temp;
	//���� �Ѿ��������� ���� ����
	for (int i = 0; i != _thisPl->getEnemyM()->getVEnemy().size(); i++)
	{
		
		if (IntersectRect(&temp, &_thisPl->getRefObj().rc,&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
		{
			if(_thisPl->getEnemyM()->getVEnemy()[i]->getState() == EN_STATE::EN_DOWN
			 || _thisPl->getEnemyM()->getVEnemy()[i]->getState() == EN_STATE::EN_WEAPONHIT)
			{
				_thisPl->setState(PL_STATE::STOMP);
				return;
			}
		}
	}

	
	//����� ���¸� ������� ���º���
	if (_thisPl->getInfo().hasWeapon) _thisPl->setState(PL_STATE::THROW);

	//���⸦ ��� ���� ������ �̹��� ����
	else _thisPl->changeImg("pl_sAttack", false);
	
	
	
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
			ATTACKSIZE* 0.2, ATTACKSIZE / 2);
		break;
	}

	//Ű�Է� ����
	_thisPl->setIsControl(false);

	//���ݿ���: �ǰݿ� �����ߴ��� Ȯ��
	if (checkEnemy()) _isCollision = true;
}

void playerSAttack::UpdateState()
{
	//�ѹ��� �ǰ�
	_thisPl->getInfo().isAttack = false;

	//�ǰݿ� �����ߴٸ� �ε�����ȣ�� ���⿡ ���� Ư�� ��ȣ�϶� ����Ʈ�� �ѹ��� ���
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_thisPl->getInfo().dest == DIRECTION::LEFT
			&&_isCollision && _thisPl->getObj().imgIndex.x >= 6)
		{
			SOUND_M->playSFX("kyoko_sAttack");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isCollision = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_thisPl->getInfo().dest == DIRECTION::RIGHT
			&&_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 6)
		{
			SOUND_M->playSFX("kyoko_sAttack");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isCollision = false;
		}
		break;
	}

	//�������� ������
	if (isEndFrame(false))
	{
		//Ű���� ������ ���·� ����
		_thisPl->setIsControl(true);
		//�Ϲ� �������� ����
		_thisPl->setState(PL_STATE::IDLE);
	}
}

void playerSAttack::ExitState()
{
}
