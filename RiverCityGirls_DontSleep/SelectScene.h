#pragma once
#include "Scene.h"
#include "Select.h"
#include <functional>

enum class SELECTTYPE
{
	LOAD,
	OPTION,
	MANUAL,
	CHARACTER,
};


class SelectScene : public Scene
{
private:
	SELECTTYPE _state;			//현재 선택 씬의 상태

	Select* _loadSelect;		//로드할 파일 선택
	Select* _charSelect;		//캐릭터 선택

	vector3 loop;				//배경 루프

	image* _background2;		//배경2

	image* _illust;				//좌측 캐릭터 일러스트
	vector3 _illustPos;
	Interpolation* _illustInter;
	float _ratioOffset;
	float _ratioTime;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void load();		//로드 버튼 콜백 함수


	void setState(SELECTTYPE type);
};

