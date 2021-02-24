#include "stdafx.h"
#include "playerJumpAttack.h"
#include "EnemyManager.h"
#include "Enemy.h"

void playerJumpAttack::EnterState()
{
	//���� ���� �Ұ�
	_thisPl->getInfo().isConDest = false;

	//�̹��� ���� �Ұ�
	_thisPl->changeImg("pl_jumpAttack",false);

	//�浹 �����ʱ�ȭ
	_isCollision = false;
	_isEffect = false;
}

void playerJumpAttack::UpdateState()
{
	RECT _temp;
	
	//���⿡ ���� ���� ��Ʈ ����
	switch (_thisPl->getInfo().dest)
	{
	case DIRECTION::LEFT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x - _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE* 0.2, ATTACKSIZE );
		break;
	case DIRECTION::RIGHT:
		_thisPl->getInfo().attackRc = RectMakeCenter(_thisPl->getObj().pos.x + _thisPl->getObj().size.x / 2,
			_thisPl->getObj().pos.z - _thisPl->getObj().size.z / 2 + _thisPl->getObj().pos.y,
			ATTACKSIZE*0.2, ATTACKSIZE );
		break;
	}
	
	//���ݿ���
	if (!_isCollision && checkEnemy())
	{
		_isCollision = true;
		_isEffect = true;
	
	}

	if (_isEffect)
	{
		//�ǰݿ� �����ߴٸ� �ε�����ȣ�� ���⿡ ���� Ư�� ��ȣ�϶� ����Ʈ�� �ѹ��� ����Ϸ��ٰ� �ε��� ��ȣ ���°� �ڿ�������Ͱ���
		switch (_thisPl->getInfo().dest)
		{
		case DIRECTION::LEFT:
			//if( _thisPl->getObj().imgIndex.x >= 4)
			{
			SOUND_M->playSFX("kyoko_jumpAttack");

			EFFECT_M->play("ef_star", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom)*0.6);
			_isEffect = false;
			}
			break;
		case DIRECTION::RIGHT:
			//if(_thisPl->getObj().imgIndex.x <= _thisPl->getObj().img->getMaxFrameX() - 4)
			{
			SOUND_M->playSFX("kyoko_jumpAttack");

			EFFECT_M->play("ef_star", (_thisPl->getInfo().attackRc.left + _thisPl->getInfo().attackRc.right) / 2,
				(_thisPl->getInfo().attackRc.top + _thisPl->getInfo().attackRc.bottom)*0.6);
			_isEffect = false;
			}
			break;
		}
	}
	//�̵�
	crossMove(_thisPl->getInfo().speed*1.2);
	lineMove(_thisPl->getInfo().speed / 2);

}

void playerJumpAttack::ExitState()
{
	_thisPl->getInfo().isAttack = false;
}
