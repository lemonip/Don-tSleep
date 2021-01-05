#include "stdafx.h"
#include "SelectScene.h"

HRESULT SelectScene::init()
{
	/*====================================================================
		선택 씬에서 세이브 파일을 로딩할 수 있게 합니다.
	====================================================================*/

	/*====================================================================
		맵의 사이즈를 지정하고, 타이틀은 UI로 취급하며, 배경은 루프시킵니다.
	====================================================================*/
	backGround = IMG_M->findImage("select_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);

	/*====================================================================
		두 캐릭터 이미지를 선형 보간으로 이동시킵니다.
	====================================================================*/
	_illust = IMG_M->findImage("select_illust");
	_illustPos = vector3(350.0f, WINSIZEY / 2 + 400.0f, 0.0f);
	_illustInter = new Interpolation;
	_illustInter->moveTo(&_illustPos, 450, WINSIZEY / 2 + 400, 0.2f);
	_ratioOffset = 0.0f;

	/*====================================================================
		UI에 선택 이미지를 추가하고, 선택할 수 있도록 합니다.
	====================================================================*/


	/*====================================================================
		카메라 움직임과 대기 이벤트를 실행합니다.
	====================================================================*/
	EVENT_M->addEvent(new waitForSec(0.3f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.1f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.8, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	return S_OK;
}

void SelectScene::release()
{
}

void SelectScene::update()
{
	_illustInter->update();

	//RND->getInt(2) == 0 ? _ratioOffset = 0.0f : _ratioOffset = 0.05f;

	/*====================================================================
		카메라는 중앙에 고정시키고, 엔터를 치면 다음 씬으로 넘깁니다.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);
	if ((KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE)) && !EVENT_M->isEvent())
	{
		SCENE_M->changeScene("loading");			//로딩 씬으로 변경
	}

}

void SelectScene::render()
{
	/*====================================================================
		배경을 loop 값에 따라 루프 렌더하고, 캐릭터 이미지를 띄워 줍니다
	====================================================================*/
	backGround->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
	IMG_M->findImage("start_frame")->render(getMapDC(), 800, 450, 1280 / 1600.0f , 720 / 900.0f);
	_illust->render(getMapDC(), _illustPos.x, _illustPos.y, 0.7f + _ratioOffset, 0.7f + _ratioOffset);
}
