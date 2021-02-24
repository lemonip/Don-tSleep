#include "stdafx.h"
#include "playerCombo1.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerCombo1::EnterState()
{
	//Ÿ�ݿ� �����ʱ�ȭ
	_isCollision = false;

	//�̹��� ����
	if (_thisPl->getInfo().attackObj)
	{
		switch (_thisPl->getInfo().attackObj->weaponType)
		{
		case WEAPON_TYPE::BAT:
			_thisPl->changeImg("pl_wBatAttack", false);
			break;
		case WEAPON_TYPE::BASEBALL:
			//_thisPl->changeImg("pl_wBatWalk", true);
			break;
		}
	}
	else _thisPl->changeImg("pl_comboAttack1", false);

	//���⿡ ���� ���� ��Ʈ ����
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x - _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE* 0.2, ATTACKSIZE/2);
		break;
	case DIRECTION::RIGHT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x + _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE*0.2, ATTACKSIZE/2);
		break;
	}

	//���ݿ���: ���ʹ̰� �ִ��� Ȯ���ϰ� ������ isAttack�� true�� �ٲ�
	if (checkEnemy())
	{
		//���Ⱑ �ִ� ���°�, ������ ����̶��
		if ( _thisPl->getInfo().attackObj != NULL && _thisPl->getInfo().attackObj->weaponType == WEAPON_TYPE::BAT )
		{
			//Ÿ�ݿ� �����ߴ��� Ȯ��
			_isCollision = true;
		}
		//�Ǽ����� ���� ���¸� ����Ʈ�� ������
		else if (_thisPl->getInfo().attackObj == NULL)
		{
			EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
			SOUND_M->playSFX("kyoko_combo");
			//Ÿ�ݿ� �����ߴ��� Ȯ��
			_isCollision = true;
		}
	}

	//Ű ���͸� �����.
	KEY_M->clearVKey();
}

void playerCombo1::UpdateState()
{
	RECT _temp;
	
	//�������� 1���� �ǵ���
	_thisPl->getInfo().isAttack = false;

	//���� ���� �ְ�, ������ �ε����� Ÿ�ֿ̹� �°� �տ� ���⸦ ��� ������
	if (_thisPl->getInfo().attackObj != NULL)
	{
		switch (_thisPl->getInfo().dest)
		{
		case DIRECTION::LEFT:
			if (_thisPl->getInfo().dest == DIRECTION::LEFT
				&&_isCollision && _thisPl->getObj().imgIndex.x >= 2)
			{
				SOUND_M->playSFX("kyoko_weapon_bat");

				EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
					(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
				_isCollision = false;
			}
			break;
		case DIRECTION::RIGHT:
			if (_thisPl->getInfo().dest == DIRECTION::RIGHT
				&&_isCollision && _thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 2)
			{
				SOUND_M->playSFX("kyoko_weapon_bat");

				EFFECT_M->play("ef_attack", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
					(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom) / 2);
				_isCollision = false;
			}
			break;
		}
	}


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
					_thisPl->setState(PL_STATE::COMBO2);

				else _thisPl->setState(PL_STATE::IDLE);

			}
		}
		else _thisPl->setState(PL_STATE::IDLE);
	}

	//================================

	//�⺻ ���� 
	basePattern();
}

void playerCombo1::ExitState()
{
}
