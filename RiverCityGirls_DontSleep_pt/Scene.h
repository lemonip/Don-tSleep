#pragma once
#include "gameNode.h"

/*====================================================================
	��� ������ ���� ��ӹ޽��ϴ�.
====================================================================*/

class Scene : public gameNode
{
protected:
	image* _background;

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

