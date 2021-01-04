#include "stdafx.h"
#include "bossMove.h"
#include "Boss.h"

void bossMove::EnterState()
{
	_count = 0;
	_count++;
	_thisBs->ChangeImg("move");
	
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
		_thisBs->ChangeImg("move");
	}
	
}

void bossMove::ExitState()
{
}
