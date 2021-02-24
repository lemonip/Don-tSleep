#pragma once

class UI;
class LocationLock;
class Video;
enum class VIDEOTYPE;

enum class DIALOGLIST;
enum class DIRECTION;
class Player;


/*====================================================================
	�̺�Ʈ Ŭ�����Դϴ�. �پ��� �̺�Ʈ���� ����ϰ� �ֽ��ϴ�.
====================================================================*/
class Event
{
public:
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
	ī�޶� �̵��� ���� ����
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
	������ ���
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
	��ȭ
====================================================================*/
class dialogue : public Event
{
	enum class DIALOGSTATE
	{
		ENTER,
		UPDATE,
		EXIT,
	};

	struct tagImg
	{
		image* _portrait;		//ĳ���� �ʻ�ȭ
		image* _name;			//ĳ���� �̸�
		vector3 _pos;			//��ġ
		vector3 _goal;			//��ǥ ��ġ
		DIRECTION _dest;		//����
		Interpolation _inter;	//���� ����
	};

private:
	DIALOGSTATE		_state;			//����

	bool			_isRender;		//�׸�����
	image*			_diaWindow;		//���â
	vector<string>	_vScript;		//��ũ��Ʈ
	int				_scriptIndex;	//��ũ��Ʈ �ε���
	
	string			_txt;			//�ؽ�Ʈ
	int				_txtIndex;		//�ؽ�Ʈ �ε���
	tagImg			_img;			//��ȭ �̹���

	DIALOGLIST		_list;			//��ȭ ����Ʈ
	
	float			_dialogTime;	//��� �ð�
	bool			_autoSkip;		//�ڵ� �ѱ�

	float			_txtTime;		//�ؽ�Ʈ �ð�
	float			_txtInterval;	//�ؽ�Ʈ���͹�
	int				_txtPos;		//�ؽ�Ʈ ��ġ

public:

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();

	dialogue(DIALOGLIST file);
	~dialogue() {}

	void render(HDC hdc);
};


/*====================================================================
	���
====================================================================*/
class waitForSec : public Event
{
private:
	float _endTime;

public:
	waitForSec(float sec);

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();
};

/*====================================================================
	������
====================================================================*/
class locationLock : public Event
{
private:
	bool _isStart;
	bool _isEnd;
 

	LocationLock* _event;
public:
	locationLock();

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();

};

/*====================================================================
	��Ʈ
====================================================================*/
class heart : public Event
{
	
private:
	image* _img;
	float _ratio;
	float _timer;
	bool _isReverse;

public:
	heart(bool reverse);

	virtual void enter(bool playerControl);
	virtual bool update();
	virtual void exit();

	void render(HDC hdc);
};