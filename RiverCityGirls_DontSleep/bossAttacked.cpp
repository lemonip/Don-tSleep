#include "stdafx.h"
#include "bossAttacked.h"
#include "Boss.h"

void bossAttacked::EnterState()
{
	LookatPlayer();
	RECT _temp;
	_enterTime = TIME_M->getWorldTime();
	_thisBs->getInfo().isAttack = true;

	// �̹����� �ٲ�
	switch (RND->getInt(3))
	{				
	case 0:
		if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{			
			_thisBs->ChangeImg("Bs_attacked1");
			SOUND_M->play("battacked1", SFXVOLUME);
		}

		if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->ChangeImg("Bs_attacked1");
			SOUND_M->play("battacked1", SFXVOLUME);
		}
		break;

	case 1:
		if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{
			_thisBs->ChangeImg("Bs_attacked2");
			SOUND_M->play("battacked2", SFXVOLUME);
		}

		if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->ChangeImg("Bs_attacked2");
			SOUND_M->play("battacked2", SFXVOLUME);
		}
		break;

	case 2:
		if (_thisBs->getInfo().dest == DIRECTION::LEFT)
		{
			_thisBs->ChangeImg("Bs_attacked3");
			SOUND_M->play("battacked3", SFXVOLUME);
		}
		if (_thisBs->getInfo().dest == DIRECTION::RIGHT)
		{
			_thisBs->ChangeImg("Bs_attacked3");
			SOUND_M->play("battacked3", SFXVOLUME);
		}
		break;
	}	
	
	ResetFrame();					//�̹��� �ʱ�ȭ
}

void bossAttacked::UpdateState()
{		
	if (_thisBs->getIsphase())
	{
		EFFECT_M->play("Bss_phase", _thisBs->getObj()->pos.x, _thisBs->getObj()->pos.z - 150);
	}

	if (TIME_M->getWorldTime() - _enterTime > 1.5f)
	{
		_thisBs->SetState(BS_STATE::WAIT);
	}	
}

void bossAttacked::ExitState()
{
	
}
