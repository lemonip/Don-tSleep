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
		스테이지의 벽을 배치합니다. LT, RT, RB, LB 순!!
	====================================================================*/
	backWallInit(vector3(430, WINSIZEY, 0), vector3(1655, WINSIZEY, 0), vector3(1655, 0, 355), vector3(430, 0, 355));

	leftWallInit(vector3(0, WINSIZEY, 0), vector3(430, WINSIZEY, 0), vector3(430, 0, 355), vector3(0, 0, 790));

	rightWallInit(vector3(1655, WINSIZEY, 0), vector3(2077, WINSIZEY, 0), vector3(2077, 0, 775), vector3(1655, 0, 355));

	floorInit(vector3(0, 0, 790), vector3(2077, 0, 770), vector3(2077, 0, 810), vector3(0, 0, 810));

	/*====================================================================
		오브젝트와 에너미를 배치합니다.
	====================================================================*/
	_enemyM->pushEnemy(ENEMY_TYPE::BOSS, vector3(WINSIZEX , 0, WINSIZEY));

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
