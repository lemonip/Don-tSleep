#include "stdafx.h"
#include "LoadingScene.h"

HRESULT LoadingScene::init()
{
	/*====================================================================
		���� ī�޶��� �� ����� �����Ѵ�.
	====================================================================*/
	_background = IMG_M->findImage("load_background");
	CAMERA_M->SetMap(*this, _background);


	/*====================================================================
		UI �ε� �ٸ� ȣ���Ѵ�.
	====================================================================*/
	_max = 300;
	_count = 0;

	UI_M->setIsActive(true);
	UI_M->addBar("loadingBar", IMG_M->findImage("bossHPFront"), IMG_M->findImage("bossHPBack"), vector3(200, 600, 0), &_count, &_max);
	UI_M->findUI("loadingBar")->setActive(true);

	/*====================================================================
		��������Ʈ �̹����� �ִϸ��̼��� �����Ѵ�.
	====================================================================*/
	_sprite = IMG_M->findImage("loading_sprite");
	ani = new animation;
	ani->init(_sprite->getWidth(), _sprite->getHeight(), _sprite->getFrameWidth(), _sprite->getFrameHeight());
	ani->setDefPlayFrame(false, true);
	ani->setFPS(1);
	ani->start();

	/*====================================================================
		�̱� �����带 ����Ѵ�.
	====================================================================*/
	CreateThread(
		NULL,				//�������� ���ȼӼ�(�ڽ������찡 �����Ҷ�)
		NULL,				//�������� ����ũ��(NULL�� �θ� ���ξ����� ũ��� ����)
		threadFunction,		//������ ����� �Լ� ��
		this,				//������ �Ű�����(this�� �θ� �� Ŭ����)
		NULL,				//�������� Ư��(��ٸ���, �ٷ� ����(NULL�̸� ��� �ش�))
		NULL				//������ ���� �� �������� ID �Ѱ��� ������ NULL�� �д�
	);
	
	return S_OK;
}

void LoadingScene::release()
{
}

void LoadingScene::update()
{
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	ani->frameUpdate(0.1f);

	//�ε��� �� �Ǹ�
	if (_count == _max)
	{
		UI_M->findUI("loadingBar")->setActive(false);
		SCENE_M->changeScene("game");
	}
}

void LoadingScene::render()
{
	_background->render(getMapDC());
	_sprite->aniRender(getMapDC(), WINSIZEX - 150, WINSIZEY - 220, ani);
}

DWORD CALLBACK threadFunction(LPVOID lpParameter)
{
	LoadingScene* helper = (LoadingScene*)lpParameter;

	while (helper->_count!=helper->_max)
	{
		Sleep(1);
		++helper->_count;
	}

	return 0;
}
