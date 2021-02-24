#include "stdafx.h"
#include "pet.h"
#define PETSPEED 3.f

HRESULT pet::init()
{
	//�ִϰ���
	_obj.init(OBJECT_GROUP::OBJECT, IMG_M->findImage("pet"), vector3(WINSIZEX/2, 0, WINSIZEY / 2));
	_obj.ani = new animation;
	_obj.ani->setDefPlayFrame(false, true);
	_obj.ani->setFPS(1);
	_obj.ani->init(_obj.img->getWidth(), _obj.img->getHeight(), _obj.img->getFrameWidth(), _obj.img->getFrameHeight());
	
	//======================================
	_xOffset = 60;
	_yOffset = -200;
	_obj.pos.y = _yOffset;
	_obj.ani->start();
	_speed = PETSPEED;
	return S_OK;
}

void pet::release()
{
}

void pet::update(vector3 pos)
{
	//�����Ӿ���
	_obj.ani->frameUpdate(TIME_M->getElapsedTime()*7);
	//������� (���� �̰ž�� ���ϴµ�;;)
	if(!_obj.ani->isPlay())_obj.ani->start();

	
	//==================================
	//���� ���� �Ÿ� �̻� �־����� ���� �ӵ��� �߰��Ѵ�.
	int revisionXSpeed = 0;
	int revisionYSpeed = 0;
	if (abs(pos.x - _obj.pos.x) > WINSIZEX / 4) revisionXSpeed = abs(pos.x - _obj.pos.x) / 30;
	if (abs(pos.y - _obj.pos.z) > WINSIZEY / 4) revisionYSpeed = abs(pos.z - _obj.pos.z) / 30;
	if (abs(pos.y - _obj.pos.y) > WINSIZEY / 4) revisionYSpeed = abs(pos.y - _obj.pos.y) / 30;
	
	//x������
	if (_obj.pos.x > pos.x +_xOffset) --_obj.pos.x;
	if (_obj.pos.x < pos.x - _xOffset) ++_obj.pos.x;

	//z�� ����
	if (_obj.pos.z > pos.z) --_obj.pos.z;
	if (_obj.pos.z < pos.z) ++_obj.pos.z;

	//y������
	if (_obj.pos.y > pos.y + _yOffset)--_obj.pos.y;
	if (_obj.pos.y < pos.y + _yOffset)++_obj.pos.y;



	if (_obj.pos.x < pos.x - _xOffset) _obj.pos.x += _speed + revisionXSpeed;
	if (_obj.pos.x > pos.x + _xOffset) _obj.pos.x -= _speed + revisionXSpeed;

	_obj.update();

}

void pet::render(HDC hdc)
{
	ZORDER_M->renderObject(hdc, &_obj, RENDERTYPE::ANI_RENDER);
}
