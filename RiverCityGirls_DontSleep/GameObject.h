#pragma once
#include "Linear.h"

/*====================================================================
	Z-Order와 충돌 처리를 위해 Player, Enemy, Object 등
	게임 오브젝트에 전체적으로 쓰이는 GameObject 클래스입니다.
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
	OBJECT_GROUP group;		//그룹

	image* img;				//이미지
	POINT imgIndex;			//프레임 인덱스
	animation* ani;			//애니메이션

	vector3 pos;			//위치
	vector3 prePos;			//이전 위치
	vector3 size;			//크기 (x,z)
	RECT rc;				//렉트

	Linear topPlane[4];		//위 평면
	Linear bottomPlane[4];	//아래 평면
	Linear sideHeight[4];	// 그리기 전용 선분들, 충돌 처리에는 안 씀

	int alpha;				//불투명도 (0~255)

	float angle;			//각도
	float zAngle;			//Z각도
	float margin;			//z여백

	bool isActive;			//활성화 여부
	bool isShadow;			//그림자가 있는지

	tagShadow shadow;		//그림자 구조체

public:
	GameObject() {}
	virtual ~GameObject() {}

	virtual void init(OBJECT_GROUP _group, image* _img, vector3 _pos);				//초기화
	virtual void init(OBJECT_GROUP _group, image* _img, vector3 _pos, float a);		//오브젝트 여백 초기화
	virtual void release();
	virtual void update();
	virtual void render();

	void RectRenew();		//렉트 갱신
	void shadowUpdate();
	void PolyLineRender(HDC hdc);	//디버깅용 선 렌더

/*====================================================================
								SETTER
====================================================================*/
	void setGOAni(animation* an) { ani = an; }
	void setPosX(float x) { pos.x = x; }
	void setPosY(float y) { pos.y = y; }
	void setPosZ(float z) { pos.z = z; }
};

