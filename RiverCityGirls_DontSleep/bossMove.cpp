#include "stdafx.h"
#include "bossMove.h"
#include "Boss.h"
#include "Player.h"

void bossMove::EnterState()
{	

	_count = 0;
	_count++;

	//_count = TIME_M->getWorldTime();

	_thisBs->ChangeImg("Bs_move");
	
}

void bossMove::UpdateState()
{

	/*_info.count++;								미완
	if (_info.count % 8 == 0)
	{
		_boss.angle = getAngle(_boss.x, _boss.y, _player.x, _player.y);

		_boss.x += cosf(_boss.angle) * _boss.speed;
		_boss.y += -sinf(_boss.angle) * _boss.speed;
	}
	if (_palyer.x >= _boss.x)
	{
		_thisBs->set 오른쪽
	}*/

	if (_count % 8 == 0)
	{
		_thisBs->ChangeImg("Bs_move");
		
	}	

	if (_thisBs->getobj().pos.x >= _thisBs->getPlayerAddress()->getObj().pos.x)
	{
		_thisBs->SetDest(BS_DEST::LEFT);
	}
	else
	{
		_thisBs->SetDest(BS_DEST::RIGHT);
	}

	if (abs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getobj().pos.x) < 100 && abs(_thisBs->getPlayerAddress()->getObj().pos.x - _thisBs->getobj().pos.z) < 20)
	{
		_thisBs->SetState(BS_STATE::SLAP);
	}
	
}

void bossMove::ExitState()
{
}
