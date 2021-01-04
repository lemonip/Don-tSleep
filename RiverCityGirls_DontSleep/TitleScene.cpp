#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	/*====================================================================
		타이틀 씬에서 인트로 등의 연출을 진행합니다.
	====================================================================*/

	/*====================================================================
		맵의 사이즈를 지정하고, 배경과 타이틀 UI를 지정합니다.
		타이틀은 UI로 취급하며, 배경은 루프시킵니다.
	====================================================================*/
	backGround = IMG_M->findImage("start_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);

	/*====================================================================
		인트로 비디오 이벤트를 실행합니다. 비디오 실행 동안은 모든 업데이트와 렌더가 멈춥니다.
	====================================================================*/
	EVENT_M->addEvent(new moviePlay(VIDEOTYPE::GAME_INTRO));

	/*====================================================================
		UI에 타이틀 이미지를 추가하고, UI 이동을 실행시킵니다.
	====================================================================*/
	_title = IMG_M->findImage("start_title");
	UI_M->setIsActive(true);
	UI_M->addImage("title", _title, { vector3(WINSIZEX / 2, WINSIZEY / 2,0) });
	UI_M->findUI("title")->setActive(true);
	UI_M->findUI("title")->move(vector3(WINSIZEX / 2 - 200, WINSIZEY / 2, 0), 3);

	/*====================================================================
		카메라 움직임과 대기 이벤트를 실행합니다.
	====================================================================*/
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.001f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.5, 0.001f));
	EVENT_M->addEvent(new waitForSec(0.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.001f));

	return S_OK;
}

void TitleScene::release()
{

}

void TitleScene::update()
{
	/*====================================================================
		카메라는 중앙에 고정시키고, 엔터를 치면 타이틀 UI를 빼고 다음 씬으로 넘깁니다.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);
	if (KEY_M->isOnceKeyDown(VK_RETURN))
	{
		UI_M->findUI("title")->setActive(false);	//title UI 비활성화
		UI_M->popUI("title");						//title UI 아예 삭제
		SCENE_M->changeScene("loading");			//씬을 변경
	}

	/*====================================================================
		배경을 x+1, y+1 대각선 방향으로 루프 시킵니다.
	====================================================================*/
	loop.x++; loop.y++;
}

void TitleScene::render()
{
	/*====================================================================
		배경을 loop 값에 따라 루프 렌더하고, 캐릭터 이미지를 띄워 줍니다
	====================================================================*/
	backGround->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
	IMG_M->findImage("start_kyoko")->render(getMapDC(), WINSIZEX / 2 + 200, WINSIZEY / 2);
}
