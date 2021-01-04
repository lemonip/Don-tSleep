#include "stdafx.h"
#include "UIManager.h"

HRESULT UIManager::init()
{
	return S_OK;
}

void UIManager::release()
{
}

/*====================================================================
					활성화된 UI를 업데이트 합니다.
====================================================================*/
void UIManager::update()
{
	if (KEY_M->isOnceKeyDown(VK_F3))
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
					활성화된 UI를 렌더 합니다.
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
					단일 이미지로 UI를 추가합니다.
====================================================================*/
void UIManager::addImage(string name, image* img, vector3 pos)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	UI* ui = new UI;
	ui->_type = UITYPE::UI;
	ui->_img = img;
	ui->_pos = pos;
	ui->_isActive = false;

	_mUI.insert(make_pair(name, ui));
}

void UIManager::addBar(string name, image * front, image * back, vector3 pos, int* current, int* max)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return;

	UI* ui = new Bar(front, back, current, max);
	ui->_pos = pos;
	ui->init();
	ui->_type = UITYPE::BAR;
	ui->_isActive = false;

	_mUI.insert(make_pair(name, ui));
}

/*====================================================================
						UI를 제거합니다.
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
		}
		else ++_miUI;
	}
}

/*====================================================================
		UI를 찾아 리턴합니다. UI 내부 함수를 사용할 수 있게 됩니다.
====================================================================*/
UI * UIManager::findUI(string name)
{
	_miUI = _mUI.find(name);
	if (_miUI != _mUI.end()) return _miUI->second;
	return nullptr;
}
