#pragma once
#include "image.h"


//����۶�� �� ��Ʈ�� �̹����� �ϳ� ���� �� �д�.
static image* _backBuffer = IMG_M->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _mapBuffer = IMG_M->addImage("mapBuffer", WINSIZEX, WINSIZEY);

class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;		//�Ŵ��� �ʱ�ȭ �� ���� ����

public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();					//�ʱ�ȭ ���� �Լ�
	virtual HRESULT init(bool managerInit);
	virtual void release();					//�޸� ���� �Լ�
	virtual void update();					//���� ����
	virtual void render();					//�׸��� ����

	//����� ������
	void setBackBuffer(int _mapXSize, int _mapYSize) { _backBuffer->init(_mapXSize, _mapYSize); }
	void setMapBuffer(int _mapXSize, int _mapYSize) { _mapBuffer->init(_mapXSize, _mapYSize); }
	
	//hdc ������
	HDC getHDC() { return _hdc; }

	//����� ������
	HDC getBackDC() { return _backBuffer->getMemDC(); }

	//�ʹ��� ������
	HDC getMapDC() { return _mapBuffer->getMemDC(); }

	LRESULT MainProc(HWND, UINT, WPARAM, LPARAM);
};

