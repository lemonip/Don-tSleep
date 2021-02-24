#include "stdafx.h"
#include "playGround.h"

#include "TitleScene.h"
#include "SelectScene.h"
#include "LoadingScene.h"
#include "GameScene.h"
#include "ShopScene.h"

// ============================ ����� �� ============================
#include <iostream>
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
using namespace std;
// ==================================================================

/*====================================================================

	�÷��̱׶��� �ʱ�ȭ�Դϴ�. �̰����� �̹����� ���� �����մϴ�.
	setScene �� changeScene�� ���� ���� ���� �����մϴ�.
	title�� �⺻�̸�, �׽�Ʈ�ϰ� ���� ���� �ִٸ� init���� �ش� ������ change ���ּ���.

====================================================================*/
HRESULT playGround::init()
{
	gameNode::init(true);
	addSource();						//�ҽ� �߰�
	addScene();							//�� ����
	SCENE_M->changeScene("title");		//ù ���۾� (title)

	return S_OK;
}

void playGround::release()
{
	gameNode::release();
}

/*====================================================================

	�÷��̱׶��� ������Ʈ�Դϴ�. �⺻������ �׻� ���� ���� ������Ʈ ������,
	���� ��� �߿��� ������ ������Ʈ�� ����� �ϹǷ� �̺�Ʈ �Ŵ�����
	������ ��� ���̶�� �ϸ� ���� ���� ������Ʈ�� ���� �ʰ� return�մϴ�.

====================================================================*/
void playGround::update()
{
	gameNode::update();						//���� ��忡�� �Ŵ������� ������Ʈ�Ѵ�.

	if (EVENT_M->getIsMovie()) return;		//���� ��� �߿��� ������Ʈ ���� �ʴ´�.
	EFFECT_M->update();						//����Ʈ�Ŵ��� ������Ʈ
	CAMERA_M->update();						//ī�޶� ������Ʈ �Ѵ�.
	UI_M->update();							//UI ������Ʈ
	SCENE_M->update();						//�� ������Ʈ
	SOUND_M->update();

	//================= ����� �� =================
	if (KEY_M->isOnceKeyDown(VK_F12)) DATA_M->checkData();
	if (KEY_M->isOnceKeyDown(VK_F7))
	{
		DATA_M->saveStageData();
		DATA_M->addData();
		DATA_M->saveIniData(DATA_M->getFileNum());
	}
	if (KEY_M->isOnceKeyDown(VK_F8))
	{
		if (DATA_M->loadIniData(DATA_M->getFileNum())) DATA_M->loadStageData();
	}
}

/*====================================================================

	�÷��� �׶��忡�� ������ �ϸ�, �⺻������ BackDC�� �Ͼ� ����� ���,
	���� ��� �߿� ���߹��۸��� ���� ���ƾ� �ϱ� ������ return�մϴ�.

	�̺�Ʈ �Ŵ����� ���� ��� ���� �ƴ� ���,
	���� mapDC�� �����ϰ�, ī�޶� map�� UI�� backDC�� �����մϴ�.
	TAB�� ����� ��� fps �� ������ ������ ����Ǹ�,
	���������� HDC�� backDC�� ���� ���۸��մϴ�.

====================================================================*/
void playGround::render()
{
	PatBlt(getBackDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);	//�Ͼ� ���
	
	//================ ���� ���� =================
	if (EVENT_M->getIsMovie()) return;	//���� ��� �߿��� �������� �ʴ´�.
	SCENE_M->render();								//�� ����
	
	CAMERA_M->render(getBackDC(),_mapBuffer);		//ī�޶� ����
	EVENT_M->render(getBackDC());					//�̺�Ʈ ����

	//================= ����� �� =================
	//FPS Ȯ��
	if (KEY_M->isToggleKey(VK_TAB)) TIME_M->render(getBackDC());
	
	//================= ���� ���۸� =================
	_backBuffer->render(getHDC());
}

/*====================================================================

	���� �����մϴ�. Ÿ��Ʋ, ����, ����, ���� �װ����� �ֽ��ϴ�.
	�������� ���ν��� ��ü�� ���� ������ �̵��� �Ұ����մϴ�.

====================================================================*/
void playGround::addScene()
{
	SCENE_M->addScene("title", new TitleScene);			//Ÿ��Ʋ �� �߰�
	SCENE_M->addScene("select", new SelectScene);		//���� �� �߰�
	SCENE_M->addScene("loading", new LoadingScene);		//�ε� �� �߰�
	SCENE_M->addScene("game", new GameScene);			//���� �� �߰�
	SCENE_M->addScene("shop", new ShopScene);			//���� �� �߰�
}
