#include "stdafx.h"
#include "UI.h"

/*====================================================================
						단일 이미지 UI
====================================================================*/
void UI::update()
{
	if (isMove)
	{
		pos.x += cosf(getAngle(pos.x, pos.y, goal.x, goal.y))*speed;
		pos.y -= sinf(getAngle(pos.x, pos.y, goal.x, goal.y))*speed;

		if (getDistance(pos.x, pos.y, goal.x, goal.y) < 10) isMove = false;
	}
}

void UI::render(HDC hdc)
{
	img->render(hdc, pos.x, pos.y);
}

void UI::move(vector3 point, float speed)
{
	goal.x = point.x;
	goal.y = point.y;
	this->speed = speed;
	isMove = true;
}

/*====================================================================
						Prgress Bar
====================================================================*/
void Bar::render(HDC hdc)
{
	img->render(hdc, pos.x, pos.y, ratio, 1);
}

/*====================================================================
						인 벤 토 리
====================================================================*/
void Inventory::render(HDC hdc)
{

}
