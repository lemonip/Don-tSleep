#include "stdafx.h"
#include "BossStage.h"

HRESULT BossStage::init()
{
	Stage::init();

	/*====================================================================
		스테이지의 배경 이미지를 설정하고, 카메라에게 맵 사이즈를 알려 줍니다.
	====================================================================*/
	backGround = IMG_M->findImage("bossStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		오브젝트와 에너미를 배치합니다.
	====================================================================*/
	_enemyM->pushEnemy(ENEMY_TYPE::BOSS, vector3(WINSIZEX / 4 + 80, 0, WINSIZEY / 2 + 40));

	/*====================================================================
		스테이지 진입 시 실행 될 이벤트를 추가합니다.
	====================================================================*/
	EVENT_M->addEvent(new moviePlay(VIDEOTYPE::BOSS_INTRO));

	return S_OK;
}

void BossStage::release()
{
	Stage::release();
}

void BossStage::update()
{
	Stage::update();
}

void BossStage::render()
{
	Stage::render();
}
