#include "stdafx.h"
#include "playerCombo3.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo3::EnterState()
{
	//�̹��� ����
	_thisPl->changeImg("pl_comboAttack3", false);

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

	//���ݿ���: �ǰݿ� �����ߴ��� Ȯ��
	if (checkEnemy()) _isCollision = true;
}

void playerCombo3::UpdateState()
{
	RECT _temp;

	//�ѹ��� �ǰ�
	_thisPl->getInfo().isAttack = false;

	//�ǰݿ� �����ߴٸ� �ε�����ȣ�� ���⿡ ���� Ư�� ��ȣ�϶� ����Ʈ�� �ѹ��� ���
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		if (_isCollision && _thisPl->getObj().imgIndex.x >= 5)
		{
			SOUND_M->playSFX("kyoko_combo");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
			(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
		_isCollision = false;
		}
		break;
	case DIRECTION::RIGHT:
		if (_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() -5)
		{
			SOUND_M->playSFX("kyoko_combo");

			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
			(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
		_isCollision = false;
		}
		break;
	}

	//�ε����� �� ���ư��� �Ϲݵ�������
	if (isEndFrame(false))_thisPl->setState(PL_STATE::IDLE);

	//�ȱ�
	walkPattern();
}

void playerCombo3::ExitState()
{
}
