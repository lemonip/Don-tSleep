#pragma once
#include "singletonBase.h"
#include <map>
#include "UI.h"

class Player;
/*====================================================================
	UI�� �ʿ� ��� �����ϴ� UI �Ŵ����Դϴ�.
====================================================================*/
class UIManager : public singletonBase <UIManager>
{
private:
	map<string, UI*> _mUI;					//UI map
	map<string, UI*>::iterator _miUI;		//UI iterator
	bool _isActive;							//��ü UI Ȱ��ȭ ����
	Player* _player;

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render(HDC hdc);
	void setLinkPlayer(Player* player) { _player = player; }

/*====================================================================
							GETTER
====================================================================*/
	bool getIsActive() { return _isActive; }

/*====================================================================
							SETTER
====================================================================*/
	void setIsActive(bool active) { _isActive = active; }

/*====================================================================
							ADD UI
====================================================================*/
	void addUI(string, image* img, vector3 pos);													//���� �̹��� UI�� �߰��Ѵ�.
	void addImage(string, image* img, vector3 pos);													//���� �̹��� UI�� �߰��Ѵ�.
	void addBar(string name, image * front, image * back, vector3 pos, int* current, int* max);		//���α׷��� �� UI�� �߰��Ѵ�.
	void addLock(string name, vector3 pos);
	void addPhone(string name);
	void addEndingUI(string name);
	void deleteAll();
/*====================================================================
							FUNCTION
====================================================================*/
	void popUI(string name);		//UI�� �����Ѵ�.

	UI* findUI(string name);		//UI�� ã�´�.

};

