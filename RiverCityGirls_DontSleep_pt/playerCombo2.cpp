#include "stdafx.h"
#include "playerCombo2.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo2::EnterState()
{

	//Ÿ�ݿ� �����ʱ�ȭ
	_isCollision = false;
	_isEffect = false;

	//�̹�������
	_thisPl->changeImg("pl_comboAttack2", false);

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

	//���ݿ���: ���ʹ̰� �ִ��� Ȯ���ϰ� ������ isAttack�� true�� �ٲ�
	if (checkEnemy())
	{
		_isCollision = true;
		_isEffect = true;
	}

	//Ű ���͸� �����.
	KEY_M->clearVKey();
}

void playerCombo2::UpdateState()
{
	RECT _temp;
	//�������� 1���� �ǵ���
	_thisPl->getInfo().isAttack = false;

	//�ǰݿ� �����ߴٸ� �ε�����ȣ�� ���⿡ ���� Ư�� ��ȣ�϶� ����Ʈ�� �ѹ��� ���
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_isEffect && _thisPl->getObj().imgIndex.x >= 2)
		{
			SOUND_M->playSFX("kyoko_combo");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isEffect = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_isEffect && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 2)
		{
			SOUND_M->playSFX("kyoko_combo");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			_isEffect = false;
		}
		break;
	}

	//���� Ű �Է� �޾Ƽ� ���Ϳ� �����ϱ�
	if (KEY_M->isOnceKeyDownV('S'));

	//�������� �� ���Ҵ�.
	if (isEndFrame(false))
	{
		//�� ���߿� S Ű�� ��������.
		if (!KEY_M->getVKeyBuffer().empty() && KEY_M->getKeyBuffer(0) == 'S' && !_thisPl->getInfo().attackObj)
		{
			for (int i = 0; i < _thisPl->getEnemyM()->getVEnemy().size(); i++)
			{
				//Ÿ���� �������, ���ʹ̿� �浹���̴�.
				if (_isCollision && IntersectRect(&_temp, &_thisPl->getInfo().attackRc,
					&(_thisPl->getEnemyM()->getVEnemy()[i]->getRefObj().rc)))
					_thisPl->setState(PL_STATE::COMBO3);
				else _thisPl->setState(PL_STATE::IDLE);
			}
		}
		else _thisPl->setState(PL_STATE::IDLE);
	}

	//�ȱ�
	walkPattern();

	//����
	if (KEY_M->isStayKeyDown('F'))_thisPl->setState(PL_STATE::GUARD);
}

void playerCombo2::ExitState()
{
}
