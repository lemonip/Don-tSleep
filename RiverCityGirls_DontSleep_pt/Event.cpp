#include "stdafx.h"
#include "Event.h"
#include "Video.h"
#include "Player.h"
#include "UI.h"
#include "EnemyManager.h"


void Event::enter(bool playerControl)
{
	_isMovie = _isCameraMove = false;
	if (_player) _player->setIsControl(playerControl);
}

void Event::exit()
{
	_isMovie = _isCameraMove = false;
	if (_player) _player->setIsControl(true);
}

/*====================================================================
	ī�޶� �̵��� ���� ���� �̺�Ʈ
====================================================================*/
cameraMove::cameraMove(vector3 goal, float moveSpeed, float mag, float magSpeed)
{
	_goal = goal;

	_goal.x += WINSIZEX / 2;
	_goal.y += WINSIZEY / 2;

	_moveSpeed = moveSpeed;
	_mag = mag;
	_magSpeed = magSpeed;
}
void cameraMove::enter(bool playerControl)
{
	Event::enter(playerControl);
	_isCameraMove = true;
}

bool cameraMove::update()
{
	CAMERA_M->SetPos(_goal.x, _goal.y, 0, 0, _moveSpeed);
	CAMERA_M->SetMagnification(_mag, _magSpeed);

	if (getDistance(CAMERA_M->GetX(), CAMERA_M->GetY(), _goal.x, _goal.y) < 50
		&& CAMERA_M->GetMagnificiation() == _mag)
	{
		CAMERA_M->SetPos(_goal.x, _goal.y);
		return true;
	}
	return false;
}

void cameraMove::exit()
{
	Event::exit();
}

/*====================================================================
	������ ��� �̺�Ʈ
====================================================================*/
moviePlay::moviePlay(VIDEOTYPE file)
{
	_video = new Video;
	switch (file)
	{
	case VIDEOTYPE::GAME_INTRO:
		_video->init("source/video/intro.wmv");
		break;

	case VIDEOTYPE::BOSS_INTRO:
		_video->init("source/video/boss.wmv");
		break;

	default:
		break;
	}
}

void moviePlay::enter(bool playerControl)
{
	Event::enter(playerControl);

	_video->play();
	_isMovie = true;
}

bool moviePlay::update()
{
	//���ͳ� �����̽��ٷ� ��ŵ
	if (_video->getIsPlaying() && (KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE))) _video->stop();

	//���� ����� �������� Ȯ��
	if (_video->getIsPlaying())
	{
		char lp[10];
		long mode = MCIWndGetMode(_video->getVideo(), lp, sizeof(lp));
		if (mode == 525)  _video->stop();	//���� ����� �����Ŵ
	}
	//���� ����� ������ ����
	if (!_video->getIsPlaying()) return true;

	return false;
}

void moviePlay::exit()
{
	Event::exit();

	//���� ������� �ƴ϶�� ��.
	_isMovie = false;

	//���� ����
	SAFE_DELETE(_video);
}

/*====================================================================
	���â�� ��ȭ �̺�Ʈ
====================================================================*/

dialogue::dialogue(DIALOGLIST file)
{
	string filePath = "source/dialog/";
	string fileName;
	{
		switch (file)
		{
		case DIALOGLIST::EASY_START:
			fileName = filePath + "easy_start.txt";
			break;
		case DIALOGLIST::BOSS_START:
			fileName = filePath + "boss_start.txt";
			break;
		case DIALOGLIST::BOSS_END:
			fileName = filePath + "boss_end.txt";
			break;
		default:
			break;
		}
	}
	_vScript = TXTDATA->txtLoad(fileName.c_str());
}

void dialogue::enter(bool playerControl)
{
	Event::enter(playerControl);
	if (_player) _player->setIsControl(false);

	_txtIndex = 0;
	_scriptIndex = 0;
	_autoSkip = true;
	_diaWindow = IMG_M->findImage("dialogWindow");
	_isRender = true;

	_img._portrait = IMG_M->findImage("shadow");
	_txtTime = TIME_M->getWorldTime();
	_txtInterval = 0.02f;

	_img._pos.x = 100;
	_img._pos.y = 500;
	_img._inter.moveTo(&_img._pos, _img._pos.x +
		cosf(getAngle(_img._pos.x, _img._pos.y, WINSIZEX / 2, _img._pos.y)) * 30, _img._pos.y, 0.3f);

	_state = DIALOGSTATE::ENTER;
}

bool dialogue::update()
{
	_img._inter.update();
	switch (_state)
	{
		case dialogue::DIALOGSTATE::ENTER:
		{	
			_dialogTime = TIME_M->getWorldTime();

			//���� �ؽ�Ʈ�� �����Ѵ�.
			_txt = _vScript[_scriptIndex];

			//�̹����� �޽����� �����Ѵ�.
			char imgfile[512];
			strncpy_s(imgfile, 512, _txt.c_str(), 510);
			char* _temp;
			strtok_s(imgfile, "@", &_temp);
			_txt = _temp;	//�ؽ�Ʈ

			if (!strcmp(imgfile, "kyoko_1") || !strcmp(imgfile, "kyoko_2") || !strcmp(imgfile, "kyoko_3")) _img._dest = DIRECTION::LEFT;
			if (!strcmp(imgfile, "misuzu_1") || !strcmp(imgfile, "misuzu_2") || !strcmp(imgfile, "misuzu_3")) _img._dest = DIRECTION::RIGHT;

			switch (_img._dest)		//�̹��� ����
			{
				case DIRECTION::LEFT:	 _img._pos.x = 100; _img._pos.y = 500;	_txtPos = 280;			break;
				case DIRECTION::RIGHT:	 _img._pos.x = WINSIZEX - 100; _img._pos.y = 500;	_txtPos = 80;  break;
			}
			_img._portrait = IMG_M->findImage(imgfile);		//�ʻ�ȭ �̹���
			//�̹����� ���� �������� �̵���Ų��.
			_img._inter.moveTo(&_img._pos, _img._pos.x + cosf(getAngle(_img._pos.x, _img._pos.y, WINSIZEX / 2, _img._pos.y)) * 30, _img._pos.y, 0.3f);

			_state = DIALOGSTATE::UPDATE;
		}
		break;
		case dialogue::DIALOGSTATE::UPDATE:
		{
			//�ڵ� ��ŵ
			if (KEY_M->isOnceKeyDown(VK_LCONTROL)) { _autoSkip = !_autoSkip; }

			//��ü ��ŵ
			if (KEY_M->isOnceKeyDown(VK_RETURN)) _scriptIndex = _vScript.size() - 1;

			//��� �� ���ھ� ���
			if (_txtIndex <= _txt.length() && TIME_M->getWorldTime() - _txtTime > _txtInterval)
			{
				_txtIndex++;
				_txtTime = TIME_M->getWorldTime();
			}

			//��� �ٷ� ���̱�
			if (_txtIndex < _txt.length() && KEY_M->isOnceKeyDown(VK_SPACE)) _txtIndex = _txt.length();

			//��� ��ŵ
			if (_txtIndex >= _txt.length()) _state = DIALOGSTATE::EXIT;

			//��ȭ ������
			if (_scriptIndex >= _vScript.size() - 1) return true;
		}
		break;
		case dialogue::DIALOGSTATE::EXIT:
		{
			if (KEY_M->isOnceKeyDown(VK_SPACE) || (_autoSkip && TIME_M->getWorldTime() - _dialogTime > strlen(_txt.c_str()) * 0.05f + 0.6f))
			{
				_scriptIndex++;
				_txtIndex = 0;
				_state = DIALOGSTATE::ENTER;
			}
		}
		break;
	}
	return false;
}

void dialogue::exit()
{
	Event::exit();
	_isRender = false;
}

void dialogue::render(HDC hdc)
{
	if (!_isRender) return;

	//���â�� �׸���.
	_diaWindow->render(hdc, WINSIZEX/2, WINSIZEY-_diaWindow->getHeight()/2);
	
	//��Ʈ�� ���� �����Ѵ�.
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 220, 255));
	HFONT font, oldFont;
	RECT rcText = RectMake(_txtPos, WINSIZEY - 135,  WINSIZEX-400, 320);
	font = CreateFont(50, 0, 0, 0, 0, false, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
	oldFont = (HFONT)SelectObject(hdc, font);

	//�ؽ�Ʈ�� ����Ѵ�.
	DrawText(hdc, TEXT(_txt.c_str()), _txtIndex, &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);

	//�̹����� ����Ѵ�.
	if (_img._portrait && _state != DIALOGSTATE::ENTER) _img._portrait->render(hdc, _img._pos.x, _img._pos.y);

	//��Ʈ�� �����Ѵ�.
	DeleteObject(font);
}

/*====================================================================
	second�� ����ϴ� �̺�Ʈ
====================================================================*/
waitForSec::waitForSec(float sec)
{
	_endTime = TIME_M->getWorldTime() + sec;
}

void waitForSec::enter(bool playerControl)
{
	Event::enter(playerControl);
	_isCameraMove = true;
}

bool waitForSec::update()
{
	if (TIME_M->getWorldTime() >= _endTime) return true;
	return false;
}

void waitForSec::exit()
{
	Event::exit();
}



/*====================================================================
	������ �̺�Ʈ
====================================================================*/
locationLock::locationLock()
{
	
}

void locationLock::enter(bool playerControl)
{
	_isMovie = false;
	_isCameraMove = true;
	if (_player) _player->setIsControl(playerControl);
	_event = (LocationLock*)UI_M->findUI("LocationLock");
	_event->resetUI();
	_event->setActive(true);
	_event->startLock();
}

bool locationLock::update()
{

	if (_player->getEnemyM()->getVEnemy().empty() && _event->getIsLockingEnd()) _event->setUnlockEnd(true);

	if (_event->isUnlockEnd() == true )
	{
		
		return true;
	}
	return false;
}

void locationLock::exit()
{
	Event::exit();
}

heart::heart(bool reverse)
{
	_isReverse = reverse;
}

/*====================================================================
	��Ʈ �̺�Ʈ
====================================================================*/
void heart::enter(bool playerControl)
{
	Event::enter(playerControl);
	if(_isReverse)_ratio = 1;
	else _ratio = 0.2f;
	_img = IMG_M->findImage("UI_heart");
	_timer = TIME_M->getWorldTime() + 0.5f;
}

bool heart::update()
{
	if (_isReverse)
	{

		//0.01���ʸ��� ������ ���δ�.
		if (TIME_M->getWorldTime() - _timer > 0.01f)
		{
			_ratio -= 0.02f;
			_timer = TIME_M->getWorldTime();
		}
		//������ 0.2���ϸ� �̺�Ʈ�� �����Ѵ�.
		if (_ratio <= 0.2f) return true;
		return false;
	}
	else
	{
		//0.01���ʸ��� ������ �ø���.
		if (TIME_M->getWorldTime() - _timer > 0.01f)
		{
			_ratio += 0.02f;
			_timer = TIME_M->getWorldTime();
		}
		//������ 1�̻��̸� �̺�Ʈ�� �����Ѵ�.
		if (_ratio >= 1.0f) return true;
		return false;
	}
}

void heart::exit()
{
	Event::exit();
}

void heart::render(HDC hdc)
{
	_img->render(hdc, WINSIZEX/2+_img->getWidth()*(1-_ratio)/2 , WINSIZEY / 2 + _img->getHeight() *(1- _ratio)/2 , _ratio, _ratio);
}
