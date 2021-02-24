#include "stdafx.h"
#include "schoolGirl.h"
#include "Player.h"
#include "StageManager.h"

#include "enemyIDLE.h"


HRESULT schoolGirl::init()
{
	Enemy::init();

	_ENEMY_TYPE = ENEMY_TYPE::SCHOOLGIRL;
	if (_stageM->getCurStage() == STAGETYPE::EASY)
	{
		_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirlIdle"), _obj.pos);
		SetState(EN_STATE::EN_IDLE);
	}
	else if (_stageM->getCurStage() == STAGETYPE::NORMAL)
	{
		switch (RND->getInt(2))
		{
		case 0:
			_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirlWIdle"), _obj.pos);
			SetState(EN_STATE::EN_WIDLE);
			break;
		case 1:
			_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirlIdle"), _obj.pos);
			SetState(EN_STATE::EN_IDLE);
			break;
		}
	}
	else if (_stageM->getCurStage() == STAGETYPE::HARD)
	{
		_obj.init(OBJECT_GROUP::ENEMY, IMG_M->findImage("schoolGirlWIdle"), _obj.pos);
		SetState(EN_STATE::EN_WIDLE);
	}


	return S_OK;
}

void schoolGirl::release()
{

}

void schoolGirl::update()
{
	Enemy::update();

	//���ݹ޾Ҵ��� ���θ� �˼�����!
	/*if (_player->getInfo().isAttack)cout << "���ݹ���" << endl;*/
	//�뽬�����ݾ��� / �������� / Ŀ�ǵ������ �Ұ��ϳ� �־����! �ѹ� �¾����� ���̻� �ȸ°�!

}
