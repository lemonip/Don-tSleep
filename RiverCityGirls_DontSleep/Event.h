#pragma once

class Video;
enum class VIDEOTYPE;

enum class DIALOGLIST;
class Player;

/*====================================================================
	이벤트 클래스입니다. 다양한 이벤트에게 상속하고 있습니다.
====================================================================*/
class Event
{
protected:
	bool _isEnd;
	bool _isMovie;
	bool _isCameraMove;
	Player* _player;

public:
	virtual void enter(bool playerControl);
	virtual bool update() = 0;
	virtual void exit();
	virtual void render(HDC hdc) {}

	bool isMovie() { return _isMovie; }
	void setLinkPlyaer(Player* player) { _player = player; }
};

/*====================================================================
	카메라 이동과 배율 조정
====================================================================*/
class cameraMove : public Event
{
private:
	vector3 _goal;
	float _moveSpeed;
	float _mag;
	float _magSpeed;

public:
	cameraMove(vector3 goal, float moveSpeed, float mag, float magSpeed);
	~cameraMove() {}

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};


/*====================================================================
	동영상 재생
====================================================================*/
class moviePlay : public Event
{
	VIDEOTYPE _videoName;
	Video* _video;

public:
	moviePlay(VIDEOTYPE fileName);

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};

/*====================================================================
	대화
====================================================================*/
class dialogue : public Event
{
private:
	vector<string>	_vScript;		//스크립트
	int				_scriptIndex;	//스크립트 인덱스

	string			_txt;			//텍스트
	int				_txtIndex;		//텍스트 인덱스

	DIALOGLIST		_list;		//대화 리스트
	string			_file;		//텍스트 파일


public:

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();

	dialogue(DIALOGLIST file);
	~dialogue() {}

	void render(HDC hdc);
};


/*====================================================================
	대기
====================================================================*/
class waitForSec : public Event
{
private:
	float _sec;
	float _endTime;

public:
	waitForSec(float sec);

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};