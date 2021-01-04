#pragma once
#include "Scene.h"

/*====================================================================
	엔딩 씬입니다. 엔딩 후에는 타이틀 씬으로 돌아갈 수 있습니다.
====================================================================*/

class EndingScene : public Scene
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};
