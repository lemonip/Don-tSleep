#pragma once
#include "animation.h"
#define MAGENTA RGB(255,0,255)

class image
{
public:

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE,	//���ҽ� ���Ϸκ���
		LOAD_FILE,		//�̹��� ���Ϸκ���
		LOAD_EMPTY,		//�� ��Ʈ�� �̹����� ������� �ְ�
		LOAD_END
	};

	typedef struct tagImageInfo
	{
		DWORD resID;	//���ҽ��� �ҷ��ö� ����� ID��
		HDC hMemDC;
		HBITMAP hBit;
		HBITMAP hOBit;
		float x;			//�ޱ� �Կ����ϴϱ� ���� ��ǥ�� float����
		float y;
		int width;			//�̹��� ��ü ����ũ��
		int height;			//�̹��� ��ü ����ũ��
		int currentFrameX;	//���� ���� ������ ��ȣ(0���� ����)
		int currentFrameY;	//���� ���� ������ ��ȣ(0���� ����)
		int maxFrameX;		//�� �� ������
		int maxFrameY;		//�� �� ������
		int frameWidth;		//�� ������ �� ����ũ��
		int frameHeight;	//�� ������ �� ����ũ��
		BYTE loadType;	//�̹��� �ҷ��� Ÿ��

		tagImageInfo()
		{
			resID = 0;
			hMemDC = NULL;
			hBit = NULL;
			hOBit = NULL;
			x = 0;
			y = 0;
			width = 0;
			height = 0;
			currentFrameX = 0;
			currentFrameY = 0;
			maxFrameX = 0;
			maxFrameY = 0;
			frameWidth = 0;
			frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	}IMAGE_INFO, *LPIMAGE_INFO;

private:
	LPIMAGE_INFO	_imageInfo;	
	CHAR*			_fileName;		//���� �̸�
	BOOL			_trans;			//Ư�� �ȼ����� �������� ����
	COLORREF		_transColor;	//������ �ȼ���

	BLENDFUNCTION	_blendFunc;		//���� ���忡 ���� �Լ�
	LPIMAGE_INFO	_blendImage;	//���� ���� ���� �̹���

public:

	image();
	~image();

	HRESULT init(int width, int height, bool alpha = false);
	HRESULT init(const char* fileName, int width, int height,
		BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	HRESULT init(const char* fileName, float x, float y,
		int width, int height, int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	HRESULT init(const char* fileName, int width, int height, 
		int frameX, int frameY,
		BOOL trans = FALSE, COLORREF transColor = FALSE, bool alpha = false);

	void release();
	void setTransColor(BOOL trans, COLORREF transColor);

	BLENDFUNCTION getBlendFunc() { return _blendFunc; }


	/*====================================================================
								���� ���� ���� ����
	====================================================================*/

	//���� �Լ� (0,0)�� �׸�.
	void render(HDC hdc);

	//�ڸ� ũ�� ����1 (DC, �׷��� X(left), �׷���Y(top), ������X(left) ������Y(top), ������ ����, ������ ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//�ڸ� ũ�� ����2 (DC, �׷��� X(left), �׷���Y(top), ������X(left) ������Y(top), ������ ����, ������ ����, ����
	void render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, int alpha);

	//�ڸ� ũ�� ����3 (DC, ���� X, ���� Y, �׷��� ũ��, ������ X, ������ Y, ������ ����, ������ ���� )
	void render(HDC hdc, int destX, int destY, int destW, int destH, int sourX, int sourY, int sourW, int sourH);

	//���� ���� (DC, ���� RC, ������ X, ������ Y)
	void loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);


	/*====================================================================
							���� ���� �Ϲ� ����
	====================================================================*/
	//���� ���� (DC, ���� X, ���� Y)
	void render(HDC hdc, int destX, int destY);

	//���� ���� (DC, ���� X, ���� Y, ����)
	void render(HDC hdc, int destX, int destY, int alpha);

	//���� ���� (DC, ���� X, ���� Y, ���� X, ���� Y)
	void render(HDC hdc, int destX, int destY, float ratioX, float ratioY);

	/*====================================================================
							���� ���� ������ ����
	====================================================================*/
	//������ ���� (DC, ���� X, ���� Y, ������ X, ������ Y)
	void frameRender(HDC hdc, int destX, int destY, int frameX, int frameY);

	//������ ���� ���� (DC, ���� X, ���� Y, ������ X, ������ Y, ����)
	void frameRender(HDC hdc, int destX, int destY, int frameX, int frameY, int alpha);


	/*====================================================================
							���� ���� �ִ� ����
	====================================================================*/
	//�ִ� ���� (DC, ���� X, ���� Y, �ִ�)
	void aniRender(HDC hdc, int destX, int destY, animation* ani);

	//�ִ� ���� ���� (DC, ���� X, ���� Y, �ִ�, ����)
	void aniRender(HDC hdc, int destX, int destY, animation* ani, int alpha);


	// =================== �� �� ===================

	inline HDC getMemDC() { return _imageInfo->hMemDC; }

	//===========================================
	// ## �̹��� ���� ������, ������ ##
	//===========================================

	inline void setX(float x) { _imageInfo->x = x; }
	inline float getX() { return _imageInfo->x; }

	inline void setY(float y) { _imageInfo->y = y; }
	inline float getY() { return _imageInfo->y; }

	inline void setCenter(float x, float y)
	{
		_imageInfo->x = x - (_imageInfo->width / 2);
		_imageInfo->y = y - (_imageInfo->height / 2);
	}

	inline float getCenterX()
	{
		return _imageInfo->maxFrameX <= 0 ?
			_imageInfo->x + (_imageInfo->width / 2) :
			_imageInfo->x + (_imageInfo->frameWidth / 2);
	}

	inline float getCenterY()
	{
		return _imageInfo->maxFrameY <= 0 ?
			_imageInfo->y + (_imageInfo->height / 2) :
			_imageInfo->y + (_imageInfo->frameHeight / 2);
	}

	inline int getWidth() { return _imageInfo->width; }
	inline int getHeight() { return _imageInfo->height; }

	inline void setFrameX(int frameX)
	{
		_imageInfo->currentFrameX = frameX;

		if (frameX > _imageInfo->maxFrameX)
		{
			_imageInfo->currentFrameX = _imageInfo->maxFrameX;
		}
	}

	inline void setFrameY(int frameY)
	{
		_imageInfo->currentFrameY = frameY;

		if (frameY > _imageInfo->maxFrameY)
		{
			_imageInfo->currentFrameY = _imageInfo->maxFrameY;
		}
	}

	inline int getMaxFrameX() { return _imageInfo->maxFrameX; }
	inline int getMaxFrameY() { return _imageInfo->maxFrameY; }

	inline int getFrameX() { return _imageInfo->currentFrameX; }
	inline int getFrameY() { return _imageInfo->currentFrameY; }

	inline int getFrameWidth() { if (_imageInfo->frameWidth == 0) return _imageInfo->width;
								else return _imageInfo->frameWidth; }

	inline int getFrameHeight() { if (_imageInfo->frameHeight == 0) return _imageInfo->height;
								else return _imageInfo->frameHeight; }
};

