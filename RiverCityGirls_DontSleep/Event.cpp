#include "stdafx.h"
#include "Event.h"
#include "Video.h"
#include "Player.h"

/*====================================================================
	카메라 이동과 배율 조정 이벤트
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
void cameraMove::enter()
{
	Event::enter();
	if(_player) _player->setIsControl(false);
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
	if (_player) _player->setIsControl(true);

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

void moviePlay::enter()
{
	Event::enter();

	_video->play();
	_isMovie = true;
}

bool moviePlay::update()
{
	//엔터로 스킵
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
	//영상 재생중이 아니라고 함.
	_isMovie = false;

	//영상 삭제
	SAFE_DELETE(_video);
}

/*====================================================================
	대사창과 대화 이벤트
====================================================================*/
void dialogue::enter()
{
	Event::enter();

}

bool dialogue::update()
{
	return true;

}

void dialogue::exit()
{
}

/*====================================================================
	second를 대기하는 이벤트
====================================================================*/
waitForSec::waitForSec(float sec)
{
	_sec = sec;
}

void waitForSec::enter()
{
	Event::enter();
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
	if (_player) _player->setIsControl(true);
}
