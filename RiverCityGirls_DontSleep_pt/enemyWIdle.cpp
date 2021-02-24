#include "stdafx.h"
#include "enemyWIdle.h"
#include "Enemy.h"

void enemyWIdle::EnterState()
{
	_thisEn->SetImage();
	_stateTimer = TIME_M->getWorldTime();
	wait = RND->getInt(2);
	if (_thisEn->getInfo().isActive)
	{
		EFFECT_M->play("ef_point", (_thisEn->getRefObj().rc.left + _thisEn->getRefObj().rc.right) / 2, _thisEn->getRefObj().rc.top);
	}
}

void enemyWIdle::UpdateState()
{
	//�÷��̾ �����ʿ� ������ ������ ������ ����. �ݴ�� ������ ����.
	LookAtPlayer();

	//�÷��̾ ������ ���� �ְ� ������ �ƴϸ� ������ �Ѵ�
	Jump();
	if ((wait && TIME_M->getWorldTime() - _stateTimer > 2.f) || !wait) //��⸦ 2�� �̻� �ϸ�
	{
		//���� ���ᰡ �ƴϰ� ������ �����Ѵ�.
		if (!_thisEn->getInfo().isFriend &&
			getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) <= 100)
		{
			_thisEn->SetState(EN_STATE::EN_WATTACK);
		}
		else
		{
			//������ ������ �ٰ�����.
			if (getDistance(_thisEn->getObj()->pos.x, _thisEn->getObj()->pos.z, _thisEn->getPlayerAddress()->getObj().pos.x, _thisEn->getPlayerAddress()->getObj().pos.z) < 200)
			{
				_thisEn->SetState(EN_STATE::EN_WWALK);
			}
			else
			{
				switch (RND->getInt(2))
				{
				case 0:
					_thisEn->SetState(EN_STATE::EN_WWALK);
					break;
				case 1:
					_thisEn->SetState(EN_STATE::EN_WRUN);
					break;
				}
			}
		}
	}
}

void enemyWIdle::ExitState()
{
	_thisEn->getInfo().isActive = false;
}
