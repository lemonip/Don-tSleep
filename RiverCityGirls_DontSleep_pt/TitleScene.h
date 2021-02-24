#pragma once
#include "Scene.h"

/*====================================================================
	Ÿ��Ʋ ���Դϴ�. �̰����� Ÿ��Ʋ ����, ���� â, �ɼ� ���� �����մϴ�.
====================================================================*/
class TitleScene : public Scene
{
private:
	vector3 loop;

	Interpolation* _titleInter;

	image* _kyoko;
	vector3 _kyokoPos;
	Interpolation* _kyokoInter;

	image* _misako;
	vector3 _misakoPos;
	Interpolation* _misakoInter;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

};

