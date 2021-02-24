#pragma once
#include "Scene.h"
#include <string>
/*====================================================================
	���� ���Դϴ�. ���� ���� �����Ͱ� �����Ǿ�� �ϹǷ� Data Manager�� �̿��մϴ�.
====================================================================*/
class shopItem
{
public:
	image* _img;
	string _name;
	string _explain;
	int _price;
	int _heal;
};

class ShopScene : public Scene
{
	vector<shopItem> _vShopItem;
	int _index;
	image* _select;
public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void ItemSet();
	void KeyInput();
};

