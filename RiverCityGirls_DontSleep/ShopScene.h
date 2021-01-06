#pragma once
#include "Scene.h"
/*====================================================================
	상점 씬입니다. 게임 씬과 데이터가 연동되어야 하므로 Data Manager를 이용합니다.
====================================================================*/
class ShopScene : public Scene
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

