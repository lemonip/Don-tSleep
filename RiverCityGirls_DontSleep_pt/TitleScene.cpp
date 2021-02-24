#include "stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init()
{
	/*====================================================================
		Ÿ��Ʋ ������ ��Ʈ�� ���� ������ �����մϴ�. ���ǰ� ��Ʈ�� ������ ����մϴ�.
	====================================================================*/
	SOUND_M->playMusic("openingBG");
	EVENT_M->addEvent(new moviePlay(VIDEOTYPE::GAME_INTRO));

	/*====================================================================
		���� ����� �����ϰ�, Ÿ��Ʋ�� UI�� ����ϸ�, ����� ������ŵ�ϴ�.
	====================================================================*/
	_background = IMG_M->findImage("start_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);

	/*====================================================================
		�� ĳ���� �̹����� ���� �������� �̵���ŵ�ϴ�.
	====================================================================*/
	_kyoko = IMG_M->findImage("start_kyoko");
	_misako = IMG_M->findImage("start_misako");

	_kyokoPos = vector3(700.0f, WINSIZEY / 2 + 200.0f, 0.0f);
	_misakoPos = vector3(1000.0f, WINSIZEY / 2 + 200.0f, 0.0f);

	_kyokoInter = new Interpolation;
	_misakoInter = new Interpolation;

	/*====================================================================
		UI�� Ÿ��Ʋ �̹����� �߰��ϰ�, UI �̵��� �����ŵ�ϴ�.
	====================================================================*/
	UI_M->setIsActive(true);
	UI_M->addImage("title", IMG_M->findImage("start_title"), vector3(WINSIZEX / 2 - 500, WINSIZEY / 2 - 100, 0));
	UI_M->findUI("title")->setActive(true);
	_titleInter = new Interpolation;

	/*====================================================================
		ī�޶� �����Ӱ� ��� �̺�Ʈ�� �����մϴ�.
	====================================================================*/
	EVENT_M->addEvent(new waitForSec(1.5f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	EVENT_M->addEvent(new waitForSec(1.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.05, 0.005f));
	EVENT_M->addEvent(new waitForSec(1.5f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.001f));

	return S_OK;
}

void TitleScene::release()
{

}

void TitleScene::update()
{
	/*====================================================================
		ī�޶�� �߾ӿ� ������ŵ�ϴ�.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	/*====================================================================
		����� x+1, y+1 �밢�� �������� ���� ��Ű��,
		ĳ���͸� ���� ������ ���� �̵���ŵ�ϴ�.
	====================================================================*/
	loop.x++; loop.y++;

	_kyokoInter->moveTo(&_kyokoPos, 1050.0f, WINSIZEY / 2 + 200.0f, 0.7f);
	_misakoInter->moveTo(&_misakoPos, 800.0f, WINSIZEY / 2 + 200.0f, 0.7f);
	_titleInter->moveTo(UI_M->findUI("title")->_pos, WINSIZEX / 2 - 500, WINSIZEY / 2 - 200, 1.0f);

	_kyokoInter->update();
	_misakoInter->update();
	_titleInter->update();

	/*====================================================================
		���͸� ġ�� Ÿ��Ʋ UI�� ���� ���� ������ �ѱ�ϴ�.
	====================================================================*/
	if ((KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE)) && !EVENT_M->getIsEvent())
	{
		UI_M->findUI("title")->setActive(false);	//title UI ��Ȱ��ȭ
		UI_M->popUI("title");						//title UI �ƿ� ����
		SCENE_M->changeScene("select");				//���� ������ ����
	}
}

void TitleScene::render()
{
	/*====================================================================
		����� loop ���� ���� ���� �����ϰ�, ĳ���� �̹����� ��� �ݴϴ�
	====================================================================*/
	_background->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
	IMG_M->findImage("start_frame")->render(getMapDC(), 800, 450, 1280 / 1600.0f, 720 / 900.0f);
	_kyoko->render(getMapDC(), _kyokoPos.x, _kyokoPos.y ,0.8f, 0.8f);
	_misako->render(getMapDC(), _misakoPos.x , _misakoPos.y, 0.8f, 0.8f);

	//��Ʈ�� ���� �����Ѵ�.
	SetBkMode(getMapDC(), TRANSPARENT);
	SetTextColor(getMapDC(), RGB(255, 255, 255));
	HFONT font, oldFont;

	//�޴���
	font = CreateFont(60, 0, 70, 0, 0, false, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
	oldFont = (HFONT)SelectObject(getMapDC(), font);
	TextOut(getMapDC(), 120, 600, "PRESS ENTER TO START!", strlen("PRESS ENTER TO START!"));

	//��Ʈ�� �����Ѵ�.
	DeleteObject(font);
}
