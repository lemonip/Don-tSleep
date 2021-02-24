#pragma once
#include "Linear.h"

/*====================================================================
	Z-Order�� �浹 ó���� ���� Player, Enemy, Object ��
	���� ������Ʈ�� ��ü������ ���̴� GameObject Ŭ�����Դϴ�.
====================================================================*/


struct tagShadow
{
	RECT rc;
	vector3 LT, RT, RB, LB;
	vector3 pos;
	float width, height;
};

class GameObject
{
public:
	GameObject* obstacle;
	OBJECT_GROUP group;		//�׷�
	OBJECT_TYPE type;		//������Ʈ Ÿ��
	OBJECT_DESTRUCTION des; //�ı����� ����
	int destructionCount;	//�ı����� Ƚ��
	WEAPON_TYPE weaponType;	//���� Ÿ��
	ITEM_TYPE itemType;		//������ Ÿ��
	
	DIRECTION dir;			//������Ʈ ����

	image* img;				//�̹���
	POINT imgIndex;			//������ �ε���
	animation* ani;			//�ִϸ��̼�
	animation* ani1;		//�ִϸ��̼�
	vector3 pos;			//��ġ
	vector3 prePos;			//���� ��ġ
	vector3 size;			//ũ�� (x,z)
	RECT rc;				//��Ʈ

	Linear topPlane[4];		//�� ���
	Linear bottomPlane[4];	//�Ʒ� ���
	Linear sideHeight[4];	// �׸��� ���� ���е�, �浹 ó������ �� ��

	int alpha;				//������ (0~255)

	float angle;			//����
	float zAngle;			//Z����
	float margin;			//z����

	bool isActive;			//Ȱ��ȭ ����
	bool isRender;			//���� ����
	bool isShadow;			//�׸��ڰ� �ִ���
	bool isBroken;			//������Ʈ �ı�����

	tagShadow shadow;		//�׸��� ����ü
	tagShadow preShadow;
public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init(OBJECT_GROUP _group, image* _img, vector3 _pos);				//�ʱ�ȭ
	virtual void init(OBJECT_GROUP _group, OBJECT_TYPE _type, image* _img, vector3 _pos, float a);		//������Ʈ ���� �ʱ�ȭ

	virtual void release();
	virtual void update();
	virtual void render();
	
/*====================================================================
								FUNCTION
====================================================================*/
	void RectRenew();		//��Ʈ ����
	void shadowUpdate();
	void PolyLineRender(HDC hdc);	//������ �� ����


/*====================================================================
								SETTER
====================================================================*/
	void setGOAni(animation* an) { ani = an; }
	void setPosX(float x) { pos.x = x; }
	void setPosY(float y) { pos.y = y; }
	void setPosZ(float z) { pos.z = z; }
};

