#include "stdafx.h"
#include "HardStage.h"

HRESULT HardStage::init()
{
	Stage::init();
	/*====================================================================
		스테이지의 배경 이미지를 설정하고, 카메라에게 맵 사이즈를 알려 줍니다.
	====================================================================*/
	backGround = IMG_M->findImage("hardStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		스테이지의 벽을 배치합니다. LT, RT, RB, LB 순!!
	====================================================================*/
	backWallInit(vector3(0, WINSIZEY, 0), vector3(1705, WINSIZEY, 0), vector3(1705, 0, 895), vector3(0, 0, 895));

	leftWallInit(vector3(0, WINSIZEY, 0), vector3(0, WINSIZEY, 0), vector3(0, 0, 1428), vector3(0, 0, 1428));

	rightWallInit(vector3(1705, WINSIZEY, 0), vector3(2235, WINSIZEY, 0), vector3(2235, 0, 1428), vector3(1705, 0, 895));

	floorInit(vector3(0, 0, 895), vector3(2328, 0, 895), vector3(2328, 0, 1428), vector3(0, 0, 1428));

	poolInit(vector3(0, 0, 1150), vector3(1480, 0, 1150), vector3(1760, 0, 1428), vector3(0, 0, 1428));
	/*====================================================================
		오브젝트와 에너미를 배치합니다.
	====================================================================*/
	_objectM->pushObject(OBJECT_TYPE::LADDER, vector3(1555, 0, 930));
	_objectM->pushObject(OBJECT_TYPE::HARDPLATFORM, vector3(850, 0, 950));
	/*====================================================================
		스테이지 진입 시 실행 될 이벤트를 추가합니다.
	====================================================================*/

	_doorActive = DOOR_ACTIVITY::NON_ACTIVE;
	_leftDoor.isUsed = true;
	_leftDoor.LT = vector3(160, 0, 890);
	_leftDoor.RT = vector3(360, 0, 890);
	_leftDoor.LB = vector3(160, 0, 940);
	_leftDoor.RB = vector3(360, 0, 940);
	UI_M->findUI("doorLeft")->setPos(&vector3((_leftDoor.LT.x + _leftDoor.RT.x) / 2, (float)0, _leftDoor.LT.z - 200));

	_rightDoor.isUsed = true;
	_rightDoor.LT = vector3(2040, 0, 1275);
	_rightDoor.RT = vector3(2250, 0, 1275);
	_rightDoor.LB = vector3(2040, 0, 1420);
	_rightDoor.RB = vector3(2250, 0, 1420);
	UI_M->findUI("doorRight")->setPos(&vector3((_rightDoor.LT.x + _rightDoor.RT.x) / 2, (float)0, _rightDoor.LT.z - 200));

	_enemyCount = 0;
	_maxEnemyCount = 10;
	return S_OK;
}

void HardStage::release()
{
	Stage::release();
}

void HardStage::update()
{
	Stage::update();
}

void HardStage::render()
{
	Stage::render();
}
