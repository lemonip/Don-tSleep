#include "stdafx.h"
#include "Event.h"
#include "Video.h"
#include "Player.h"

/*====================================================================
	카메라 이동과 배율 조정 이벤트
====================================================================*/
cameraMove::cameraMove(vector3 goal, float moveSpeed, float mag, float magSpeed)
{
	_isCameraMove = true;

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
}

bool cameraMove::update()
{
	CAMERA_M->SetPos(_goal.x, _goal.y, 0, 0, _moveSpeed);
	CAMERA_M->SetMagnification(_mag, _magSpeed);

	if (getDistance(CAMERA_M->GetX(), CAMERA_M->GetY(), _goal.x, _goal.y) < 10)
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
	동영상 재생 이벤트
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
	//엔터나 스페이스바로 스킵
	if (_video->getIsPlaying() && (KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE))) _video->stop();

	//영상 재생이 끝났는지 확인
	if (_video->getIsPlaying())
	{
		char lp[10];
		long mode = MCIWndGetMode(_video->getVideo(), lp, sizeof(lp));
		if (mode == 525)  _video->stop();	//영상 재생을 종료시킴
	}
	//영상 재생이 끝남을 리턴
	if (!_video->getIsPlaying()) return true;

	return false;
}

void moviePlay::exit()
{
	Event::exit();

	//영상 재생중이 아니라고 함.
	_isMovie = false;

	//영상 삭제
	SAFE_DELETE(_video);
}

/*====================================================================
	대사창과 대화 이벤트
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
}

bool dialogue::update()
{
	_txt = _vScript[_scriptIndex];
	
	//자동 스킵
	if (KEY_M->isOnceKeyDown(VK_LCONTROL)) { _autoSkip = !_autoSkip; }

	//전체 스킵
	if (KEY_M->isOnceKeyDown(VK_RETURN)) _scriptIndex = _vScript.size() - 1;

	if (_txtIndex <= _txt.length()) _txtIndex++;

	//대사 스킵
	else if (_txtIndex >= _txt.length())
	{
		if (KEY_M->isOnceKeyDown(VK_SPACE) || (_autoSkip && TIME_M->getWorldTime() - _dialogTime > 2.0f))
		{
			_scriptIndex++;
			_txtIndex = 0;
			_dialogTime = TIME_M->getWorldTime();
		}
	}

	//대사 바로 보이기
	if (_txtIndex < _txt.length() && KEY_M->isOnceKeyDown(VK_SPACE)) _txtIndex = _txt.length();

	//대화 끝내기
	if (_scriptIndex >= _vScript.size() - 1) return true;

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
	
	//대사창을 그린다.

	_diaWindow->render(hdc, WINSIZEX/2, WINSIZEY-_diaWindow->getHeight()/2);
	
	//폰트에 대해 설정한다.
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 220, 255));
	HFONT font, oldFont;
	RECT rcText = RectMake(200, WINSIZEY - 135, WINSIZEX - 400, WINSIZEY);
	font = CreateFont(50, 0, 0, 0, 0, false, false, false,
		DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
	oldFont = (HFONT)SelectObject(hdc, font);

	//텍스트를 출력한다.
	DrawText(hdc, TEXT(_txt.c_str()), _txtIndex, &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);

	DeleteObject(font);
}

/*====================================================================
	second를 대기하는 이벤트
====================================================================*/
waitForSec::waitForSec(float sec)
{
	_isCameraMove = true;

	_sec = sec;
}

void waitForSec::enter(bool playerControl)
{
	Event::enter(playerControl);
	if (_player) _player->setIsControl(false);

	_endTime = TIME_M->getWorldTime() + _sec;
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

void Event::enter(bool playerControl)
{
	_isEnd = _isMovie = _isCameraMove = false;
	_player->setIsConDest(playerControl);
}

void Event::exit()
{
	_player->setIsControl(true);
}
