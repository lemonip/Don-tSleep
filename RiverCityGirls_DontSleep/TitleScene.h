#pragma once
#include "Scene.h"

/*====================================================================
	타이틀 씬입니다. 이곳에서 타이틀 연출, 선택 창, 옵션 등을 실행합니다.
====================================================================*/
class TitleScene : public Scene
{
private:
	vector3 loop;
	image* _title;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

