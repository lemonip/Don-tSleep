#include "stdafx.h"
#include "StageManager.h"

#include "Player.h"
#include "CollisionManager.h"

#include "Stage.h"
#include "EasyStage.h"
#include "NormalStage.h"
#include "HardStage.h"
#include "BossStage.h"

/*====================================================================
	�ʱ�ȭ���� �÷��̾ ����� �ָ�, ù ���������� �����մϴ�.
	�⺻ ���� EASY�̸�, �����ϰ� ���� ���������� �����ϸ� �ش� ���������� ���õ˴ϴ�.
====================================================================*/
HRESULT StageManager::init()
{
	//�÷��̾� ��ü ����
	_player = new Player;
	_player->init();
	_player->setLinkStageM(this);
	EVENT_M->setLinkPlayer(_player);

	//ù �������� ����
	if (DATA_M->getStage(DATA_M->getFileNum()) == -1) setStage(STAGETYPE::EASY);

	return S_OK;
}

/*====================================================================
	Player�� Stage�� �޸𸮸� ������ �ݴϴ�.
====================================================================*/
void StageManager::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_stage->release();
	SAFE_DELETE(_stage);
}


/*====================================================================
	Player�� Stage�� ���� �� ������Ʈ �ϸ�,
	�̺�Ʈ�� ���� ������ ���� ������ ī�޶� �÷��̾ ���� ���ϴ�.
====================================================================*/
void StageManager::update()
{
	_stage->update();
	_player->update();

	if (!EVENT_M->getIsCameraMove()) CAMERA_M->SetPos(_player->getObj().pos.x, _player->getObj().pos.z + _player->getObj().pos.y, 0, 0, 4.5f);

	changeStage();
#ifdef _DEBUG
	// ����׿� �������� �̵�
	if (KEY_M->isOnceKeyDown(VK_F1)) setStage(STAGETYPE::EASY);
	if (KEY_M->isOnceKeyDown(VK_F2)) setStage(STAGETYPE::NORMAL);
	if (KEY_M->isOnceKeyDown(VK_F3)) setStage(STAGETYPE::HARD);
	if (KEY_M->isOnceKeyDown(VK_F4)) setStage(STAGETYPE::BOSS);
#endif
}

/*====================================================================
	Player�� Stage�� ���� �մϴ�.
====================================================================*/
void StageManager::render()
{
	_stage->render();
	_player->render();
}

/*====================================================================
	setStage �Լ��� enum class STAGETYPE�� ���ڰ����� �޾�,
	���� ���������� �ش� ���������� ���� �� �ݴϴ�.
====================================================================*/
void StageManager::setStage(STAGETYPE current)
{
	if (_stage != NULL)
	{
		if (_currentStage == current) return;	//���� ���������� ���� ��� ���������� �ٲ��� �ʴ´�.

		_stage->release();		//���������� ������� ������, �ٲٱ� ����
		SAFE_DELETE(_stage);	//�޸𸮸� ���� �ְ� ����Ʈ �� �ش�.
	}

	_preStage = _currentStage;
	_currentStage = current;	//���� ���������� �ٲ� �ش�.
	if(_currentStage != STAGETYPE::BOSS) EVENT_M->addEvent(new heart(false), false);

	//���ο� �������� ��ü�� �����ϰ�, �ʱ�ȭ�Ѵ�.
	switch (_currentStage)
	{
	case STAGETYPE::EASY:
		_stage = new EasyStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;

	case STAGETYPE::NORMAL:
		_stage = new NormalStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;

	case STAGETYPE::HARD:
		_stage = new HardStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;

	case STAGETYPE::BOSS:
		_stage = new BossStage;
		_stage->setLinkStageM(this);
		_stage->init();
		break;
	}

	//�÷��̾ �������� �ʱ�ȭ�� �Ѵ�.
	_player->stageInit();
}

void StageManager::changeStage()
{
	if (EVENT_M->getIsEvent()) return;
	if (getStage()->getLockEventStart() == false || getStage()->getLockEventEnd() == true)
	{
		if (KEY_M->isStayKeyDown('M'))
		{
			_keyTimer += TIME_M->getElapsedTime();
			if (_keyTimer >= 1.0f || true)
			{
				switch (_currentStage)
				{
				case STAGETYPE::EASY:
					if (_stage->getRightDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getRightDoor().RB.z &&
						_stage->getRightDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getRightDoor().RB.x)
					{
						setStage(STAGETYPE::NORMAL);
						_keyTimer = 0;
					}
					break;
				case STAGETYPE::NORMAL:
					if (_stage->getLeftDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getLeftDoor().RB.z &&
						_stage->getLeftDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getLeftDoor().RB.x)
					{
						setStage(STAGETYPE::EASY);
						_keyTimer = 0;
					}
					else if (_stage->getRightDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getRightDoor().RB.z &&
						_stage->getRightDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getRightDoor().RB.x)
					{
						setStage(STAGETYPE::HARD);
						_keyTimer = 0;
					}
					else if (_stage->getShopDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getShopDoor().RB.z &&
						_stage->getShopDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getShopDoor().RB.x)
					{
						SOUND_M->playSFX("shop_voice");
						DATA_M->saveStageData();
						SCENE_M->setInitScene("shop");	//���� ����
						_keyTimer = 0;
					}
					break;

				case STAGETYPE::HARD:
					if (_stage->getLeftDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getLeftDoor().RB.z &&
						_stage->getLeftDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getLeftDoor().RB.x)
					{
						setStage(STAGETYPE::NORMAL);
						_keyTimer = 0;
					}
					else if (_stage->getRightDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getRightDoor().RB.z &&
						_stage->getRightDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getRightDoor().RB.x)
					{
						setStage(STAGETYPE::BOSS);
						_keyTimer = 0;
					}
					break;
				case STAGETYPE::BOSS:
					if (_stage->getLeftDoor().LT.z <= _player->getObj().pos.z &&
						_player->getObj().pos.z <= _stage->getLeftDoor().RB.z &&
						_stage->getLeftDoor().LT.x <= _player->getObj().pos.x &&
						_player->getObj().pos.x <= _stage->getLeftDoor().RB.x)
					{
						setStage(STAGETYPE::HARD);
						_keyTimer = 0;
					}
					break;
				default:
					break;
				}
			}

		}
	}
}
