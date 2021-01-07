#pragma once

class Video;
enum class VIDEOTYPE;
class Player;

/*====================================================================
	이벤트 클래스입니다. 다양한 이벤트에게 상속하고 있습니다.
====================================================================*/
class Event
{
protected:
	bool _isEnd;
	bool _isMovie;
	Player* _player;

public:
	virtual void enter() { _isEnd = false; _isMovie = false; }
	virtual bool update() = 0;
	virtual void exit() = 0;
	virtual void render() {}

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

	virtual void enter();
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

	virtual void enter();
	virtual bool update();
	virtual void exit();
};

/*====================================================================
	대화
====================================================================*/
class dialogue : public Event
{
private:
	struct tagInfo
	{
		image* portrait;		//캐릭터 초상화
		image* name;			//캐릭터 이름
		vector3 pos;			//위치
		vector3 goal;			//목표 지점
	};

	struct tagSkip
	{
		//UI* bar;				//스킵 프로그레스 바
		float curGauge;			//현재 게이지
		float maxGauge;			//최대 게이지
		bool isStayDown;		//누르는 중
	};

	enum class curDialogue
	{
		ENTER,	//이미지를 화면으로 가져오기
		WRITE,	//대사를 출력 하기
		EXIT,	//이미지를 화면 밖으로 빼기
	};

	enum class DIALOGUELIST
	{
		INTRO,
		BOSS_BEFORE,
		BOSS_AFTER,
	};

	queue<string>	_qMsg;		//대사
	queue<tagInfo>	_qInfo;		//정보
	tagSkip			_skip;		//스킵
	string			_writeText;	//최종 출력
	curDialogue		_curDia;	//

	bool			_isPlay;	//현재 진행 중
	float			_imgSpeed;	//이미지 속도
	float			_textSpeed;	//텍스트 속도
	float			_elpaSec;	//시간 계산
	int				_stringNum;	//출력할 글자 위치
	float			_textTerm;	//텍스트 출력 후 화면 넘어가는 텀
	float			_textY;		//텍스트 개행 시 Y축 위치 조절

public:

	virtual void enter();
	virtual bool update();
	virtual void exit();

	dialogue(DIALOGUELIST chapter, float textSpeed);
	~dialogue() {}

	HRESULT init(float textSpeed);
	void render();

	void startChapter(DIALOGUELIST chapter);
	bool getIsPlay() { return _isPlay; }

	bool textUpdate(float elapsedTime);
	bool findNameImg(string src, string name);
	void keyReaction();
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

	virtual void enter();
	virtual bool update();
	virtual void exit();
};