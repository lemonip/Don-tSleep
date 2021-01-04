#include "stdafx.h"
#include "GameObject.h"

//초기화 (그룹, 이미지, 위치)
void GameObject::init(OBJECT_GROUP _group, image* _img, vector3 _pos)
{
	img = _img;
	group = _group;

	pos = _pos;
	angle = - PI / 4;
	size.x = img->getFrameWidth();
	size.z = img->getFrameHeight();

	alpha = 255;

	RectRenew();

	switch (group)
	{
	case OBJECT_GROUP::PLAYER:
		isShadow = true;
		break;
	case OBJECT_GROUP::ENEMY:
		isShadow = true;
		break;
	case OBJECT_GROUP::BOSS:
		isShadow = true;
		break;
	case OBJECT_GROUP::OBJECT:
		isShadow = false;
		break;
	case OBJECT_GROUP::ITEM:
		isShadow = false;
		break;
	default:
		break;
	}

	isActive = true;
}

void GameObject::init(OBJECT_GROUP _group, image* _img, vector3 _pos, float a)
{
	img = _img;
	group = _group;

	pos = _pos;
	angle2 = a;
	angle = -PI / 4;
	size.x = img->getFrameWidth();
	size.z = img->getFrameHeight();

	alpha = 255;

	RectRenew();

	switch (group)
	{
	case OBJECT_GROUP::PLAYER:
		isShadow = true;
		break;
	case OBJECT_GROUP::ENEMY:
		isShadow = true;
		break;
	case OBJECT_GROUP::BOSS:
		isShadow = true;
		break;
	case OBJECT_GROUP::OBJECT:
		topPlane[0] = Linear(vector3(pos.x - size.x / 2 + angle2, -size.z + angle2, pos.z - size.z), vector3(pos.x + size.x / 2, -size.z + angle2, pos.z - size.z));					// 위쪽 선분
		topPlane[1] = Linear(vector3(pos.x + size.x / 2, -size.z + angle2, pos.z - size.z), vector3(pos.x + size.x / 2 - angle2, -size.z + angle2, pos.z - size.z + angle2));			// 오른쪽 선분
		topPlane[2] = Linear(vector3(pos.x + size.x / 2 - angle2, -size.z + angle2, pos.z - size.z + angle2), vector3(pos.x - size.x / 2, -size.z + angle2, pos.z - size.z + angle2)); // 밑쪽 선분
		topPlane[3] = Linear(vector3(pos.x - size.x / 2, -size.z + angle2, pos.z - size.z + angle2), vector3(pos.x - size.x / 2 + angle2, -size.z + angle2, pos.z - size.z));			// 왼쪽 선분

		bottomPlane[0] = Linear(vector3(pos.x - size.x / 2 + angle2, (float)0, pos.z - angle2), vector3(pos.x + size.x / 2, (float)0, pos.z - angle2));			// 위쪽 선분
		bottomPlane[1] = Linear(vector3(pos.x + size.x / 2, (float)0, pos.z - angle2), vector3(pos.x + size.x / 2 - angle2, (float)0, pos.z));					// 오른쪽 선분
		bottomPlane[2] = Linear(vector3(pos.x + size.x / 2 - angle2, (float)0, pos.z), vector3(pos.x - size.x / 2, (float)0, pos.z));							// 밑쪽 선분
		bottomPlane[3] = Linear(vector3(pos.x - size.x / 2, (float)0, pos.z), vector3(pos.x - size.x / 2 + angle2, (float)0, pos.z - angle2));					// 왼쪽 선분

		// 그리기 전용 선분들, 충돌처리에서는 안쓸꺼임
		sideHeight[0] = Linear(topPlane[0].getStart(), bottomPlane[0].getStart());
		sideHeight[1] = Linear(topPlane[1].getStart(), bottomPlane[1].getStart());
		sideHeight[2] = Linear(topPlane[2].getStart(), bottomPlane[2].getStart());
		sideHeight[3] = Linear(topPlane[3].getStart(), bottomPlane[3].getStart());

	case OBJECT_GROUP::ITEM:
		isShadow = false;
		break;
	default:
		break;
	}

	isActive = true;
}

void GameObject::release()
{

}

void GameObject::update()
{
	RectRenew();
}

void GameObject::render()
{

}

void GameObject::RectRenew()
{
	rc = RectMakeCenter(pos.x, pos.z - size.z / 2 + pos.y, size.x, size.z);
}

void GameObject::PolyLineRender(HDC hdc)
{
	if (KEY_M->isToggleKey(VK_TAB))
	{
		for (int i = 0; i < 4; ++i)
		{
			topPlane[i].LinearRender(hdc);
			bottomPlane[i].LinearRender(hdc);
			sideHeight[i].LinearRender(hdc);
		}
	}
}
