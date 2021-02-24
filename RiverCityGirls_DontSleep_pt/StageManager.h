#pragma once


class Player;
class Boss;
class Stage;
class CollisionManager;

/*====================================================================
	StageManager��, �÷��̾�� ���������� ����� ������,
	������������ Easy, Normal, Hard, Boss�� �ֽ��ϴ�.
	���������� '���� �������� ����'�� �����ϸ�, ���� �������� �����մϴ�.
====================================================================*/

class StageManager
{
	Player* _player;
	Boss* _boss;
	Stage* _stage;
	STAGETYPE _currentStage;
	STAGETYPE _preStage;
	CollisionManager* _colM;
	float _keyTimer;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void changeStage();

	/*====================================================================
									SETTER
	====================================================================*/
	virtual void setStage(STAGETYPE current);
	virtual void setLinkColM(CollisionManager* col) { _colM = col; }

	/*====================================================================
									GETTER
	====================================================================*/
	Stage* getStage() { return _stage; }
	Player* getPlayer() { return _player; }
	Boss* getBoss() { return _boss; }
	STAGETYPE getCurStage() { return _currentStage; }
	STAGETYPE getPreStage() { return _preStage; }
	CollisionManager* getColM() { return _colM; }
};

