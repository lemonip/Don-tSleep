#pragma once
#include "gameNode.h"

#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

/*====================================================================
	���� Ŭ�����Դϴ�. ���� ��θ� �Է��ϸ� �ش� ������ ����մϴ�.
====================================================================*/

class Video : public gameNode
{
private:

	HWND _video;			//����
	char _file[30];			//���� ���
	bool _isPlaying;		//��� ����

public:

	virtual HRESULT init(const char* videoFile);

	void play();	//���
	void stop();	//����

	bool getIsPlaying() { return _isPlaying; }
	HWND getVideo() { return _video; }
};