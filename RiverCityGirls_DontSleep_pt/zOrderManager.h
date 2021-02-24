#pragma once
#include "singletonBase.h"

class GameObject;
enum class RENDERTYPE;

/*====================================================================
		Z���� ���� ���� �� �� ���� �� �ִ� �Ŵ����Դϴ�.
		tagZorder�� Zorder�� ���� ������ ��ü ����ü�Դϴ�.
====================================================================*/

struct tagZorder 
{
public:
	tagZorder() {}
	~tagZorder() {}

	HDC hdc;			//�׸� hdc
	image* img;			//�̹���
	animation* ani;		//�ִϸ��̼�
	POINT imgIndex;		//������ �ε���

	vector3 pos;		//��ġ
	vector3 zPos;		//Sorting�� pos
	vector3 size;		//ũ��
	RECT rc;			//��Ʈ
	bool isShadow;		//�׸��� ����
	int alpha;			//������
	RENDERTYPE renderType;	//���� ����

	bool yOffset;
};

class zOrderManager : public singletonBase <zOrderManager>
{
private:
	vector<tagZorder> _vZorder;

public:
	zOrderManager() {}
	~zOrderManager() {}

	HRESULT init();
	void release();
	void update();
	void render();

	//���Ϳ� ������Ʈ�� �ִ´�.
	void renderObject(HDC hdc, GameObject* go, RENDERTYPE renderType);
	
	//���͸� �����Ѵ�.
	void sortVector(int s, int e);

};

