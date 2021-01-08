#include "stdafx.h"
#include "schoolGirl.h"
#include "Player.h"

#include "enemyIDLE.h"


HRESULT schoolGirl::init()
{
	Enemy::init();
	//이미지 등록도 안해놓고                            ▼ schoolGirlIdle 라고 써놓으면 터지지..ㅠㅠ 
	_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirlIdle"),_obj.pos);

	SetState(EN_STATE::EN_IDLE);
	_dest = DIRECTION::RIGHT;

	return S_OK;
}

void schoolGirl::release()
{

}

void schoolGirl::update()
{
	Enemy::update();
	//_EState->UpdateState();
	//SetState(EN_STATE::EN_IDLE);
	//공격받았는지 여부를 알수있음!
	if (_player->getInfo().isAttack)cout << "공격받음" << endl;
	//대쉬강공격어택 / 점프어택 / 커맨드어택은 불값하나 있어야함! 한번 맞았으면 더이상 안맞게!
}

void schoolGirl::render()
{

}
