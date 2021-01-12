#pragma once
#include "gameNode.h"
#include "Object.h"
#define PARTICLEMAX 60
/*====================================================================
	������Ʈ �Ŵ����Դϴ�. ������Ʈ�� ���Ϳ� �־� �����ϸ�,
	push�� ������Ʈ�� ���� ���� �� �ֽ��ϴ�.
====================================================================*/
class ObjectManager : public gameNode
{
private:
	vector<Object*> _vObject;
	vector<Object*> _vParticleLeftUp;
	vector<Object*> _vParticleLeftDown;
	vector<Object*> _vParticleRightUp;
	vector<Object*> _vParticleRightDown;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	Object* findHardPlatform();
	void particleInit(vector3 pos, OBJECT_TYPE type);
	void particleSwitch(OBJECT_TYPE type);


/*====================================================================
								GETTER
====================================================================*/
	vector<Object*> getVObject() { return _vObject; }

/*====================================================================
								FUNCTION
====================================================================*/
	void pushObject(OBJECT_TYPE type, vector3 pos);		//������Ʈ�� �ִ´�.
	void pushItem(ITEM_TYPE type, vector3 pos);			//�������� �ִ´�.
	void pushWeapon(WEAPON_TYPE type, vector3 pos);		//���⸦ �ִ´�.

	void popObject(int index);						//������Ʈ�� �����Ѵ�.
};

