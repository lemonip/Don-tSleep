#include "stdafx.h"
#include "zOrderManager.h"
#include "GameObject.h"
#include "gameNode.h"

HRESULT zOrderManager::init()
{
	return S_OK;
}

void zOrderManager::release()
{
	_vZorder.clear();
}

void zOrderManager::update()
{
}

/*====================================================================
		�� Zorder �� ���� �����ϰ� ���� �� ��, ���͸� ����.
====================================================================*/
void zOrderManager::render()
{
	// ���Ͱ� ������� return�Ѵ�.
	if (_vZorder.empty()) return;

	//������ ���Ҹ� ó������ ������ �����Ѵ�.
	sortVector(0, _vZorder.size() - 1);

	//SHIFT ��� Ű�� ������ ������ Rect�� �׸���.
	if (KEY_M->isToggleKey(VK_SHIFT))
	{
		for (int i = 0; i < _vZorder.size(); i++)Rectangle(_vZorder[i].hdc, _vZorder[i].rc);
	}

	//�׸��ڰ� ������ �����Ѵ�.
	for (int i = 0; i < _vZorder.size(); i++)
	{
		
		if (_vZorder[i].isShadow)
		{
			
				IMG_M->findImage("shadow")->render(_vZorder[i].hdc, _vZorder[i].pos.x, _vZorder[i].pos.z, (((int)_vZorder[i].pos.y - 1) % 255));	//���� ���� �������� �ٲٱ�
			
		}
	}

	//�̹����� �����Ѵ�.
	for (int i = 0; i < _vZorder.size(); i++)
	{
		switch (_vZorder[i].renderType)
		{
			case RENDERTYPE::RENDER:
				_vZorder[i].img->render(_vZorder[i].hdc, _vZorder[i].pos.x, _vZorder[i].pos.y + _vZorder[i].pos.z - _vZorder[i].img->getFrameHeight() / 2, _vZorder[i].alpha);
			break;
			case RENDERTYPE::FRAME_RENDER:
				_vZorder[i].img->frameRender(_vZorder[i].hdc, _vZorder[i].pos.x, _vZorder[i].pos.y + _vZorder[i].pos.z - _vZorder[i].img->getFrameHeight() / 2, _vZorder[i].imgIndex.x, _vZorder[i].imgIndex.y, _vZorder[i].alpha);
				break;
			case RENDERTYPE::ANI_RENDER:
				_vZorder[i].img->aniRender(_vZorder[i].hdc, _vZorder[i].pos.x, _vZorder[i].pos.y + _vZorder[i].pos.z - _vZorder[i].img->getFrameHeight() / 2, _vZorder[i].ani, _vZorder[i].alpha);
			break;
		}
	}

	//���͸� ����.
	_vZorder.clear();
}

/*====================================================================
		�ش� ������Ʈ�� ���Ϳ� �־� �����ϰ� �����.
====================================================================*/
void zOrderManager::renderObject(HDC hdc, GameObject* go, RENDERTYPE renderType)
{
	tagZorder zOrder;
	zOrder.hdc = hdc;
	zOrder.img = go->img;
	zOrder.isShadow = go->isShadow;

	zOrder.pos = go->pos;
	zOrder.size = go->size;
	zOrder.rc = go->rc;
	zOrder.alpha = go->alpha;

	zOrder.renderType = renderType;
	zOrder.imgIndex = go->imgIndex;
	zOrder.ani = go->ani;


	_vZorder.push_back(zOrder);

}

/*====================================================================
		���͸� �����Ѵ�.
====================================================================*/
void zOrderManager::sortVector(int s, int e)
{
	if (s >= e) return;

	float pivot = _vZorder[s].pos.z - _vZorder[s].pos.y;
	int left = s;
	int right = e;

	while (left <= right)
	{
		//left�� pivot�� ��, left�� ������ ++
		while (_vZorder[left].pos.z - _vZorder[left].pos.y < pivot) ++left;

		//right�� pivot�� ��, left�� ũ�� --
		while (_vZorder[right].pos.z - _vZorder[right].pos.y > pivot) --right;

		//left�� right ���� ������ ������ ������.
		if (left <= right)
		{
			swap(_vZorder[left], _vZorder[right]);
			++left; --right;
		}
	}

	//����Լ��� �¿츦 ������ �� �����Ѵ�.
	sortVector(s, right);
	sortVector(left, e);
}
