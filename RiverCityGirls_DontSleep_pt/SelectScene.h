#pragma once
#include "Scene.h"
#include "Select.h"
#include <functional>

/*====================================================================
	���þ��Դϴ�. �ε�, ĳ����, �޴���� �����Ǿ� �ֽ��ϴ�.
====================================================================*/
enum class SELECTTYPE
{
	LOAD,
	CHARACTER,
	MANUAL,
};


class SelectScene : public Scene
{
private:
	SELECTTYPE _state;			//���� ���� ���� ����

	Select* _loadSelect;		//�ε��� ���� ����
	Select* _charSelect;		//ĳ���� ����

	vector3 loop;				//��� ����

	image* _background2;		//���2

	image* _illust;				//���� ĳ���� �Ϸ���Ʈ
	vector3 _illustPos;
	Interpolation* _illustInter;
	float _ratioOffset;
	float _ratioTime;

	bool _kyokoSelect;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void load(int n);	//�ε� ��ư �ݹ� �Լ�
	void load0();		//�ε� ��ư �ݹ� �Լ�
	void load1();		//�ε� ��ư �ݹ� �Լ�
	void load2();		//�ε� ��ư �ݹ� �Լ�
	void load3();		//�ε� ��ư �ݹ� �Լ�

	void character0();	//ĳ���� ��ư �ݹ� �Լ�
	void character1();	//ĳ���� ��ư �ݹ� �Լ�




	void setState(SELECTTYPE type);
};

