#include "stdafx.h"
#include "UI.h"

HRESULT UI::init()
{
	return S_OK;
}

void UI::release()
{
}

/*====================================================================
						단일 이미지 UI
====================================================================*/
void UI::update()
{
}

void UI::render(HDC hdc)
{
	_img->render(hdc, _pos->x, _pos->y);
}

/*====================================================================
						Prgress Bar
====================================================================*/

Bar::Bar(image * front, image * back, int* currentGauge, int* maxGauge)
{
	_front = front;
	_back = back;
	_current = currentGauge;
	_max = maxGauge;
}

HRESULT Bar::init()
{
	_ratio = *_current / *_max;
	_rc = RectMakeCenter(_pos->x, _pos->y, _back->getWidth(), _back->getHeight());
	return S_OK;
}
void Bar::release()
{

}
void Bar::update()
{
	_ratio = (float)*_current / (float)*_max;
}
void Bar::render(HDC hdc)
{
	//Bar는 x, y가 Left Top 기준으로 그려진다.
	_back->render(hdc, _pos->x + _back->getWidth() / 2, _pos->y + _back->getHeight() / 2);
	_front->render(hdc, _pos->x, _pos->y, 0, 0, _front->getWidth()*_ratio, _front->getHeight());			//잘라 그리는 버전
	//_front->render(hdc, _pos.x + _front->getWidth() / 2, _pos.y + _back->getHeight() / 2, _ratio, 1); //비율로 축소 시켜 그리는 버전

}

HRESULT CallPhone::init()
{
	return E_NOTIMPL;
}

void CallPhone::release()
{
}

void CallPhone::update()
{
}

/*====================================================================
						핸 드 폰
====================================================================*/
void CallPhone::render(HDC hdc)
{

}

/*====================================================================
						옵 션
====================================================================*/
HRESULT Option::init()
{
	return S_OK;
}

void Option::release()
{
}

void Option::update()
{
}

void Option::render(HDC hdc)
{
}
