#include "stdafx.h"
#include "ShopScene.h"

HRESULT ShopScene::init()
{
	/*====================================================================
		���� ������ ���忡 ������ �����մϴ�. ��������� �־��ݴϴ�.
	====================================================================*/
	SOUND_M->playMusic("shopBG");

	/*====================================================================
		���� ����� �����մϴ�.
	====================================================================*/
	_background = IMG_M->findImage("shop_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	/*====================================================================
		������ �������� �߰��մϴ�.
	====================================================================*/
	ItemSet();
	_index = 0;



	return S_OK;
}

void ShopScene::release()
{
}

void ShopScene::update()
{
	KeyInput();
}

/*====================================================================
	���� ������, ���� ���� ���� �����մϴ�.
====================================================================*/
void ShopScene::render()
{
	_background->render(getMapDC());

	_select->render(getMapDC(), 1010 - _index * 15, 280 + 80 * _index);

	//��Ʈ�� ���� �����Ѵ�.
	SetBkMode(getMapDC(), TRANSPARENT);
	SetTextColor(getMapDC(), RGB(0, 0, 0));
	HFONT font, oldFont;

	//�޴���
	font = CreateFont(30, 0, 0, 0, 0, false, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
	oldFont = (HFONT)SelectObject(getMapDC(), font);
	TextOut(getMapDC(), 50, 650, "B:���� / X:������", strlen("B:���� / X:������"));

	//���� �������� �̹����� �ؽ�Ʈ�� ����Ѵ�.
	for (int i = 0; i < 4; i++)
	{
		if(i==_index)SetTextColor(getMapDC(), RGB(255, 255, 255));
		if(i!=_index)SetTextColor(getMapDC(), RGB(0, 0, 0));

		//�̹���
		_vShopItem[i]._img->render(getMapDC(), 880 - i * 15, 250 + 80 * i);

		//�̸��� ����
		font = CreateFont(30, 0, -70, 0, 0, false, false, false,
			DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
		oldFont = (HFONT)SelectObject(getMapDC(), font);
		TextOut(getMapDC(), 930 - i * 15, 230 + 80 * i, _vShopItem[i]._name.c_str(), strlen(_vShopItem[i]._name.c_str()));
		TextOut(getMapDC(), 1050 - i * 15, 250 + 80 * i, to_string(_vShopItem[i]._price).c_str(), strlen(to_string(_vShopItem[i]._price).c_str()));

		//����
		font = CreateFont(20, 0, -70, 0, 0, false, false, false,
			DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
		oldFont = (HFONT)SelectObject(getMapDC(), font);
		TextOut(getMapDC(), 930 - i * 15, 270 + 80 * i, _vShopItem[i]._explain.c_str(), strlen(_vShopItem[i]._explain.c_str()));
	}

	//��Ʈ�� �����Ѵ�.
	DeleteObject(font);
}

/*====================================================================
	�������� �Ǹ��ϴ� �������� �����մϴ�.
====================================================================*/
void ShopScene::ItemSet()
{
	for (int i = 0; i < 4; i++)
	{
		shopItem item;
		_vShopItem.push_back(item);
	}
	_vShopItem[0]._img = IMG_M->findImage("shop_aloe");
	_vShopItem[0]._name = "�˷ο�";
	_vShopItem[0]._explain = "20 ȸ�� / �˷ο� ���� ���� �����";
	_vShopItem[0]._price = 200;
	_vShopItem[0]._heal = 20;

	_vShopItem[1]._img = IMG_M->findImage("shop_hamburger");
	_vShopItem[1]._name = "�ܹ���";
	_vShopItem[1]._explain = "40 ȸ�� / ������ ���� ������ ��Ƽ ����";
	_vShopItem[1]._price = 400;
	_vShopItem[1]._heal = 40;

	_vShopItem[2]._img = IMG_M->findImage("shop_icecream");
	_vShopItem[2]._name = "���̽�ũ��";
	_vShopItem[2]._explain = "10 ȸ�� / ���̽�ũ���� ����� ���� �ĸ���";
	_vShopItem[2]._price = 100;
	_vShopItem[2]._heal = 10;

	_vShopItem[3]._img = IMG_M->findImage("shop_tempura");
	_vShopItem[3]._name = "��Ǫ��";
	_vShopItem[3]._explain = "80 ȸ�� / �������� �̷� �� �� ����";
	_vShopItem[3]._price = 800;
	_vShopItem[3]._heal = 80;

	_select = IMG_M->findImage("ShopScene_list");
}

/*====================================================================
	Ű �Է����� ������ ������ �����ϰų� �����ϴ�.
====================================================================*/
void ShopScene::KeyInput()
{
	if (KEY_M->isOnceKeyDown(VK_DOWN))
	{
		SOUND_M->playSFX("menu_cursor");
		_index++;
		if (_index >= 4) _index = 3;
	}

	if (KEY_M->isOnceKeyDown(VK_UP))
	{
		SOUND_M->playSFX("menu_cursor");
		_index--;
		if (_index < 0) _index = 0;
	}

	//����
	if (KEY_M->isOnceKeyDown('B'))
	{
		int price = _vShopItem[_index]._price;
		int heal = _vShopItem[_index]._heal;
		if (DATA_M->minusPlayerCoin(price))
		{
			SOUND_M->playSFX("menu_confirm");
			DATA_M->plusPlayerHP(heal);
		}
	}

	//������
	if (KEY_M->isOnceKeyDown('X'))
	{
		SCENE_M->setPrevScene();
		CAMERA_M->SetMap(*this, IMG_M->findImage("normalStage"));
		DATA_M->loadStageData();
		/*====================================================================
		��������� �־��ݴϴ�.
		====================================================================*/
		SOUND_M->playMusic("hardStageBG");
	}
}
