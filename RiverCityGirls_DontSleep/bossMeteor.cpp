#include "stdafx.h"
#include "bossMeteor.h"
#include "Boss.h"
#include "Player.h"

void bossMeteor::EnterState()
{
	_angle = PI / 2;
	_speed = 8.0f;
	_enterTime = TIME_M->getWorldTime();
	_thisBs->ChangeImg("Bs_meteor");
}

void bossMeteor::UpdateState()
{
	if (TIME_M->getWorldTime() - _enterTime > 0.5f && TIME_M->getWorldTime() - _enterTime < 10.0f)
	{
		_angle = getAngle(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z,
			_thisBs->getPlayerAddress()->getPObj()->pos.x, _thisBs->getPlayerAddress()->getPObj()->pos.z);
		_thisBs->getObj()->pos.x += cosf(_angle) * _speed;
		_thisBs->getObj()->pos.z += -sinf(_angle) * _speed;

<<<<<<< HEAD
		_thisBs->getinfo().attackRC = RectMakeCenter(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z, 100, 100);
=======
		_thisBs->getIsInfo().rcAttack = RectMakeCenter(_thisBs->getobj().pos.x, _thisBs->getobj().pos.z, 100, 100);
>>>>>>> origin/靾橅槃鞛戩梾
		RECT _temp;
		//if(IntersectRect(&_temp, & _thisBs->getIsInfo().attackRC,& )) 面倒贸府 鞘夸, 敲饭捞绢 泛飘? 
		// 拳搁困肺 棵妨辑 弊贰厚萍甫 罐霸 秦辑 官蹿父 面倒阑 老栏虐芭唱, 
		// 捞固瘤 贸府肺 面倒...(?)
		// 瘤加 贸府 鞘夸
	}
}

void bossMeteor::ExitState()
{
}
