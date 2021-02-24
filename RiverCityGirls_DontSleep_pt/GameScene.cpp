#include "stdafx.h"
#include "GameScene.h"

#include "StageManager.h"
#include "CollisionManager.h"
#include "Player.h"

HRESULT GameScene::init()
{
	/*====================================================================
		���� ���� �������� �Ŵ����� �ݸ��� �Ŵ����� �����ϴ�.
	====================================================================*/
	_stageM = new StageManager;
	_stageM->init();

	_colM = new CollisionManager;

	_colM->setLinkStageM(_stageM);
	_colM->setLinkPlayer(_stageM->getPlayer());
	_stageM->getPlayer()->setLinkColM(_colM);
	_stageM->setLinkColM(_colM);

	/*====================================================================
		�����͸Ŵ����� �����Ű��, �����͸� �ҷ����� ������ ����մϴ�.
	====================================================================*/
	DATA_M->setLinkStageM(_stageM);
	DATA_M->setLinkPlayer(_stageM->getPlayer());

	DATA_M->loadStageData();
	SOUND_M->playMusic("stageBG");

	/*====================================================================
		UI�� �̹����� �߰��մϴ�.
	====================================================================*/
	UI_M->addLock("LocationLock", vector3(WINSIZEX / 2, 0, WINSIZEY / 2));

	//���� �� �̹���
	UI_M->setIsActive(true);
	UI_M->addImage("UI_kyoko", IMG_M->findImage("UI_kyoko"), vector3(20, 20, 0));
	UI_M->findUI("UI_kyoko")->setActive(true);

	UI_M->addImage("UI_coin", IMG_M->findImage("UI_coin"), vector3(140, 110, 0));
	UI_M->findUI("UI_coin")->setActive(true);
	
	//���� HP��
	for (int i = 0; i < PLAYERHP; i++)
	{
		_playerHP[i].img = IMG_M->findImage("playerHPPoint");
		_playerHP[i].pos.x = -55 + 12 * i;
		_playerHP[i].pos.y = -52;
	}

	
	return S_OK;
}

void GameScene::release()
{
	_stageM->release();
	SAFE_DELETE(_stageM);
}

void GameScene::update()
{
	_stageM->update();
}

void GameScene::render()
{
	/*====================================================================
		�������� �Ŵ����� ���� ��Ű��, Z-Order�� ���� ������ �����մϴ�.
	====================================================================*/
	_stageM->render();		//��������
	ZORDER_M->render();		//Z ����
	EFFECT_M->render();		//����Ʈ ����
	PlayerUI();				//�÷��̾� UI
}

void GameScene::PlayerUI()
{
	//UI ��ġ
	vector3 cameraPos = vector3(CAMERA_M->GetX(), CAMERA_M->GetY(), 0.0f);
	cameraPos.x -= WINSIZEX / 3; cameraPos.y -= WINSIZEY / 3;

	//�÷��̾� ü�� ��
	IMG_M->findImage("playerHPBar")->render(getMapDC(), 120 + cameraPos.x, -20 + cameraPos.y);

	//�÷��̾� ü�� ������
	for (int i = 0; i < PLAYERHP*((float)_stageM->getPlayer()->getInfo().hp / _stageM->getPlayer()->getInfo().maxHP); i++)
	{
		_playerHP[i].img->render(getMapDC(), _playerHP[i].pos.x + cameraPos.x, _playerHP[i].pos.y + cameraPos.y);
	}

	//�÷��̾� ��

	//��Ʈ�� ���� �����Ѵ�.
	SetBkMode(getMapDC(), TRANSPARENT);
	SetTextColor(getMapDC(), RGB(255, 255, 255));
	HFONT font, oldFont;

	font = CreateFont(30, 0, 0, 0, 0, true, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
	oldFont = (HFONT)SelectObject(getMapDC(), font);

	//���� ~1�ڸ���
	int coin = _stageM->getPlayer()->getInfo().coin / 100;
	string _coin = to_string(coin);
	TextOut(getMapDC(), 25 + cameraPos.x - strlen(_coin.c_str()) * 10, -10 + cameraPos.y, _coin.c_str(), strlen(_coin.c_str()));
	TextOut(getMapDC(), 35 + cameraPos.x, -10 + cameraPos.y, ".", strlen("."));

	//���� �Ҽ��� 1��° �ڸ���
	int coin1 = (_stageM->getPlayer()->getInfo().coin / 10) % 10;
	string _coin1 = to_string(coin1);
	TextOut(getMapDC(), 45 + cameraPos.x, -10 + cameraPos.y, _coin1.c_str(), strlen(_coin1.c_str()));

	//���� �Ҽ��� 2��° �ڸ���
	int coin2 = _stageM->getPlayer()->getInfo().coin % 10;
	string _coin2 = to_string(coin2);
	TextOut(getMapDC(), 60 + cameraPos.x, -10 + cameraPos.y, _coin2.c_str(), strlen(_coin2.c_str()));

	//��Ʈ�� �����Ѵ�.
	DeleteObject(font);
}
