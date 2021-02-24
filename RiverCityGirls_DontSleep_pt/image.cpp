#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0, 0, 0))
{
}

image::~image()
{
}

HRESULT image::init(int width, int height, bool alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	if (alpha)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 2, WINSIZEY * 2);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX * 2;
		_blendImage->height = WINSIZEY * 2;
	}

	if (_imageInfo == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);
	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor, bool alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//Ư�� Į���� ������ ����

	_transColor = transColor;	//�� ���� Į��
	if (alpha)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 2, WINSIZEY * 2);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX * 2;
		_blendImage->height = WINSIZEY * 2;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//Ư�� Į���� ������ ����
	_transColor = transColor;	//�� ���� Į��

	if (alpha)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 2, WINSIZEY * 2);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX * 2;
		_blendImage->height = WINSIZEY * 2;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, bool alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;				//Ư�� Į���� ������ ����
	_transColor = transColor;	//�� ���� Į��


	if (alpha)
	{
		//���ĺ��� ����
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, WINSIZEX * 2, WINSIZEY * 2);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = WINSIZEX * 2;
		_blendImage->height = WINSIZEY * 2;
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}

	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);

	}

}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;				//Ư�� Į���� ������ ����
	_transColor = transColor;	//�� ���� Į��
}

/*====================================================================
	Left Top�� �������� 0, 0�� �׸��� ����. ��� ���� �׸� �� ����Ѵ�.
====================================================================*/
void image::render(HDC hdc)
{
	render(hdc, _imageInfo->width / 2, _imageInfo->height / 2);
}

/*====================================================================
	�̹����� �߶� Left Top�� �������� ����. (Loop Render���� ���)
====================================================================*/
void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourW, int sourH)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,					//����� ������  DC
			destX, destY,			//����� ��ǥ
			sourW, sourH,			//����� ũ��
			_imageInfo->hMemDC,		//�����ؿ� DC
			sourX, sourY,			//�����ؿ� ��ǥ
			sourW, sourH,			//������ ũ��
			_transColor
		);
	}
	else
	{
		//�갡 �װ��Դϴ� DC���� ���� ��Ӻ��縦 ���ִ� �Լ�
		BitBlt(hdc,					//������ DC
			destX, destY,			//����� ��ǥ Y
			sourW, sourH,			//������ ũ��
			_imageInfo->hMemDC,		//����� DC
			sourX, sourY,			//����� ������
			SRCCOPY);				//�������� �����Ұ���
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int alpha)
{
	//���� �̹��� �ҽ��� ���ĺ��带 ���� �����ִ� �Լ� BYTE == ���� 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight,
			hdc,
			destX, destY, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight,
			_imageInfo->hMemDC,
			sourX, sourY,
			sourWidth, sourHeight, _transColor);

		AlphaBlend(hdc, destX, destY, sourWidth,
			sourHeight, _blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX, destY, sourWidth,
			sourHeight, _blendImage->hMemDC, 0, 0,
			sourWidth, sourHeight, _blendFunc);
	}
}

/*====================================================================
	�̹����� �߶� Left Top�� �������� ����. (Camera Map���� ���)
====================================================================*/
void image::render(HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,		//����� ������  DC
			destX, destY,			//����� ��ǥ
			destW, destH,			//����� ũ��
			_imageInfo->hMemDC,		//������ �� DC
			sourX, sourY,			//������ �� ��ǥ
			sourW, sourH,			//������ ����ũ��
			_transColor				//��ȯ�� ����
		);
	}
	else
	{
		SetStretchBltMode(hdc, HALFTONE);

		StretchBlt(
			hdc,					//����� ������ DC
			destX, destY,			//����� ��ǥ
			destW, destH,			//����� ũ��
			_imageInfo->hMemDC,		//������ �� DC
			sourX, sourY,			//������ �� ��ǥ
			sourW, sourH,			//������ ũ��
			SRCCOPY);				//���� ���� �����Ұ���
	}
}
/*====================================================================
	���� �������� �׷��� ��ġ�� ���ϴ� ����.
====================================================================*/

//�Ϲ� ����
void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(hdc,											//����� ������  DC
			destX - _imageInfo->width / 2, destY - _imageInfo->height / 2,	//����� X, Y ��ǥ
			_imageInfo->width, _imageInfo->height,						//����� ����, ���� ũ��
			_imageInfo->hMemDC,											//�����ؿ� DC
			0, 0,														//�����ؿ� ��ǥ X, Y
			_imageInfo->width, _imageInfo->height,						//������ ����, ���� ũ��
			_transColor													//��ȯ�� ����
		);
	}
	else
	{
		BitBlt(hdc,															//������ DC
			destX - _imageInfo->width / 2, destY - _imageInfo->height / 2,	//����� X, Y ��ǥ
			_imageInfo->width, _imageInfo->height,							//����� ����, ���� ũ��
			_imageInfo->hMemDC,												//����� DC
			0, 0,															//������ �� X, Y ��ǥ
			SRCCOPY);														//���� ���� �����Ұ���
	}
}

//���� ����
void image::render(HDC hdc, int destX, int destY, int alpha)
{
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX - _imageInfo->width / 2, destY - _imageInfo->height / 2, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width,
			_imageInfo->height, _transColor);

		AlphaBlend(hdc, destX - _imageInfo->width / 2, destY - _imageInfo->height / 2, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX - _imageInfo->width / 2, destY - _imageInfo->height / 2, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

//���� ����
void image::render(HDC hdc, int destX, int destY, float ratioX, float ratioY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,								//����� ������  DC
			destX - _imageInfo->width / 2,		//����� ��ǥ X
			destY - _imageInfo->height / 2,		//����� ��ǥ Y
			_imageInfo->width * ratioX,			//������ ����ũ��
			_imageInfo->height * ratioY,		//������ ����ũ��
			_imageInfo->hMemDC,					//�����ؿ� DC
			0, 0,								//�����ؿ� ��ǥ X, Y
			_imageInfo->width,					//������ ����ũ��
			_imageInfo->height,					//������ ����ũ��
			_transColor
		);
	}
	else
	{
		SetStretchBltMode(hdc, HALFTONE);

		StretchBlt(hdc,							//������ DC
			destX - _imageInfo->width / 2,		//����� ��ǥ X
			destY - _imageInfo->height / 2,		//����� ��ǥ Y
			_imageInfo->width * ratioX,			//������ ����ũ��
			_imageInfo->height * ratioY,		//������ ����ũ��
			_imageInfo->hMemDC,					//����� DC
			0, 0,								//�����ؿ� ��ǥ X, Y
			_imageInfo->width,					//������ ����ũ��
			_imageInfo->height,					//������ ����ũ��
			SRCCOPY);							//�������� �����Ұ���
	}
}

/*====================================================================
	���� �������� �������� �׸��� ������ ����
====================================================================*/

//�Ϲ� ����
void image::frameRender(HDC hdc, int destX, int destY, int frameX, int frameY)
{
	_imageInfo->currentFrameX = frameX;
	_imageInfo->currentFrameY = frameY;

	if (_trans)
	{
		GdiTransparentBlt(hdc,			//����� ������  DC
			destX - _imageInfo->frameWidth / 2,
			destY - _imageInfo->frameHeight / 2,	//����� ��ǥ
			_imageInfo->frameWidth,		//����� ũ�� (����)
			_imageInfo->frameHeight,	//����� ũ�� (����)
			_imageInfo->hMemDC,			//�����ؿ� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,		//������ ����ũ��
			_imageInfo->frameHeight,	//������ ����ũ��
			_transColor
		);
	}
	else
	{
		BitBlt(hdc,									//������ DC
			destX - _imageInfo->frameWidth / 2,
			destY - _imageInfo->frameHeight / 2,	//����� ��ǥ
			_imageInfo->frameWidth,					//������ ũ��
			_imageInfo->frameHeight,
			_imageInfo->hMemDC,						//����� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//����� ������ (left, top)
			SRCCOPY);								//�������� �����Ұ���
	}
}

//���� ����
void image::frameRender(HDC hdc, int destX, int destY, int frameX, int frameY, int alpha)
{
	_imageInfo->currentFrameX = frameX;
	_imageInfo->currentFrameY = frameY;

	//���� �̹��� �ҽ��� ���ĺ��带 ���� �����ִ� �Լ� BYTE == ���� 0 ~ 255
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			hdc, destX - _imageInfo->frameWidth / 2, destY - _imageInfo->frameHeight / 2, SRCCOPY);

		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _imageInfo->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight, _transColor);

		AlphaBlend(hdc, destX - _imageInfo->frameWidth / 2, destY - _imageInfo->frameHeight / 2, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
	else
	{
		AlphaBlend(hdc, destX - _imageInfo->frameWidth / 2, destY - _imageInfo->frameHeight / 2, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

/*====================================================================
	���� �������� �ִϸ��̼��� �׸��� �ִ� ����
====================================================================*/

//�Ϲ� ����
void image::aniRender(HDC hdc, int destX, int destY, animation * ani)
{
	render(hdc, destX - ani->getFrameWidth() / 2, destY - ani->getFrameWidth() / 2,
		ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight());
}

//���� ����
void image::aniRender(HDC hdc, int destX, int destY, animation * ani, int alpha)
{
	render(hdc, destX - ani->getFrameWidth() / 2, destY - ani->getFrameWidth() / 2,
		ani->getFramePos().x, ani->getFramePos().y,
		ani->getFrameWidth(), ani->getFrameHeight(), alpha);
}


/*====================================================================
	��Ʈ�� Left Top�� �������� �� ���� ����
====================================================================*/
void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	//������ ������
	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawAreaX;
	int drawAreaH = drawArea->bottom - drawAreaY;

	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//�׷��;��� ������ŭ�� ������
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//�׷��� ���� ������
		sourHeight = rcSour.bottom - rcSour.top;

		//�ٽ� �ѷ����� ������ �����ؼ� ������ �Ѹ� ������.
		if (y + sourHeight > drawAreaH)
		{
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//�׷��;��� ������ŭ�� ������
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}
}
