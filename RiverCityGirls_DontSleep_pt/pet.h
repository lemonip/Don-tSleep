#pragma once
#include "gameNode.h"
#include "GameObject.h"

class pet :public GameObject
{
	GameObject _obj;
	float _xOffset, _yOffset;	//������
	float _speed;
public:
	pet() {};
	~pet() {};
	virtual HRESULT init();		//�ʱ�ȭ
	virtual void release();		//����
	virtual void update(vector3 pos);		//������Ʈ
	virtual void render(HDC hdc);		//����
};

