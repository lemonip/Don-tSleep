#include "stdafx.h"
#include "UIManager.h"
#include "Player.h"

HRESULT UIManager::init()
{
	return S_OK;
}

void UIManager::release()
{

}

/*====================================================================
					Ȱ��ȭ�� UI�� ������Ʈ �մϴ�.
====================================================================*/
void UIManager::update()
{
	if (KEY_M->isOnceKeyDown(VK_F9))
	{
		_isActive = !_isActive;
	}

	if (_mUI.empty()) return;
	if (!_isActive) return;

	for (auto _miUI = _mUI.begin(); _miUI != _mUI.end(); ++_miUI)
	{
		if (!_miUI->second->_isActive) continue;
		_miUI->second->update();
	}
}

/*====================================================================
					Ȱ��ȭ�� UI�� ���� �մϴ�.
====================================================================*/
void UIManager::render(HDC hdc)
{
	if (_mUI.empty()) return;
	if (!_isActive) return;

	for (auto _miUI = _mUI.begin(); _miUI != _mUI.end(); ++_miUI)
	{
		if (!_miUI->second->_isActive) continue;
		_miUI->second->render(hdc);
	}
}

/*====================================================================
					���� �̹����� UI�� �߰��մϴ�.
====================================================================*/
void UIManager::addUI(string name, image * img, vector3 pos)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	UI* ui = new UI;
	ui->_type = UITYPE::UI;
	ui->_img = img;
	ui->_pos = new vector3(pos.x, pos.y, pos.z);
	ui->_isActive = false;

	_mUI.insert(make_pair(name, ui));
}
void UIManager::addImage(string name, image* img, vector3 pos)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	UI* ui = new UI;
	ui->_type = UITYPE::UI;
	ui->_img = img;
	ui->_pos = new vector3(pos.x, pos.y, pos.z);
	ui->_isActive = false;

	_mUI.insert(make_pair(name, ui));
}

void UIManager::addBar(string name, image * front, image * back, vector3 pos, int* current, int* max)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	UI* ui = new Bar(front, back, current, max);
	ui->_pos = new vector3(pos.x, pos.y, pos.z);
	ui->init();
	ui->_type = UITYPE::BAR;
	ui->_isActive = false;

	_mUI.insert(make_pair(name, ui));
}

void UIManager::addLock(string name, vector3 pos)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	UI* ui = new LocationLock();
	ui->_pos = new vector3(pos.x, pos.y, pos.z);
	ui->init();
	ui->_type = UITYPE::LOCATIONLOCK;
	ui->_isActive = false;

	_mUI.insert(make_pair(name, ui));
}

void UIManager::addPhone(string name)
{
	//ui �̸� ������ �߰� �̹� ������ �߰����� �ʰ� ����
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	//�����ϰ� �̴�
	UI* ui = new CallPhone();
	ui->init();
	ui->setLinkPlayer(_player);
	ui->_type = UITYPE::INVENTORY;
	ui->_isActive = false;

	_mUI.insert(make_pair(name, ui));
}

void UIManager::addEndingUI(string name)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	UI* ui = new EndingUI();
	ui->init();
	ui->_type = UITYPE::UI;
	ui->_isActive = false;

	_mUI.insert(make_pair(name, ui));
}

void UIManager::deleteAll()
{
	_miUI = _mUI.begin();

	for (; _miUI != _mUI.end();)
	{
		if (_miUI->second != NULL)
		{
			_miUI->second->release();
			SAFE_DELETE(_miUI->second);
			_miUI = _mUI.erase(_miUI);
		}
		else ++_miUI;
	}

	_mUI.clear();
}

/*====================================================================
						UI�� �����մϴ�.
====================================================================*/
void UIManager::popUI(string name)
{
	if (_mUI.empty()) return;

	for (auto _miUI = _mUI.begin(); _miUI != _mUI.end();)
	{
		if (name == _miUI->first)
		{
			SAFE_DELETE(_miUI->second);
			_miUI = _mUI.erase(_miUI);
			break;
		}
		else ++_miUI;
	}
}

/*====================================================================
		UI�� ã�� �����մϴ�. UI ���� �Լ��� ����� �� �ְ� �˴ϴ�.
====================================================================*/
UI * UIManager::findUI(string name)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return _miUI->second;
	return nullptr;
}
