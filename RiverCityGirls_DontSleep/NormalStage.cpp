#include "stdafx.h"
#include "NormalStage.h"

HRESULT NormalStage::init()
{
	Stage::init();
	/*====================================================================
		스테이지의 배경 이미지를 설정하고, 카메라에게 맵 사이즈를 알려 줍니다.
	====================================================================*/
	backGround = IMG_M->findImage("normalStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		스테이지의 벽을 배치합니다. LT, RT, RB, LB 순!!
	====================================================================*/
	backWallInit(vector3(260, WINSIZEY, 0), vector3(932, WINSIZEY, 0), vector3(932, 0, 500), vector3(260, 0, 500));
	backWallInit(vector3(980, WINSIZEY, 0), vector3(1640, WINSIZEY, 0), vector3(1640, 0, 550), vector3(980, 0, 550));
	backWallInit(vector3(1745, WINSIZEY, 0), vector3(2500, WINSIZEY, 0), vector3(2500, 0, 445), vector3(1745, 0, 445));

	leftWallInit(vector3(0, WINSIZEY, 0), vector3(260, WINSIZEY, 0), vector3(260, 0, 500), vector3(0, 0, 760));
	leftWallInit(vector3(1640, WINSIZEY, 0), vector3(1745, WINSIZEY, 0), vector3(1745, 0, 445), vector3(1640, 0, 550));

	rightWallInit(vector3(932, WINSIZEY, 0), vector3(980, WINSIZEY, 0), vector3(980, 0, 550), vector3(932, 0, 500));
	rightWallInit(vector3(2500, WINSIZEY, 0), vector3(2865, WINSIZEY, 0), vector3(2865, 0, 795), vector3(2500, 0, 445));

	floorInit(vector3(0, 0, 760), vector3(2865, 0, 795), vector3(2865, 0, 837), vector3(0, 0, 837));

	/*====================================================================
		오브젝트와 에너미를 배치합니다.
	====================================================================*/
	_objectM->pushObject(OBJECT_TYPE::TABLE, vector3(440, 0, 755));
	_objectM->pushObject(OBJECT_TYPE::TABLE, vector3(1000, 0, 850));
	_objectM->pushObject(OBJECT_TYPE::TABLE, vector3(1650, 0, 830));
	_objectM->pushObject(OBJECT_TYPE::TABLE, vector3(2300, 0, 750));
	_objectM->pushObject(OBJECT_TYPE::VENDINGMACHINE, vector3(2400, 0, 500));



	/*====================================================================
		스테이지 진입 시 실행 될 이벤트를 추가합니다.
	====================================================================*/

	return S_OK;
}

void NormalStage::release()
{
	Stage::release();
}

void NormalStage::update()
{
	Stage::update();
}

void NormalStage::render()
{
	Stage::render();
}
