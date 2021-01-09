#include "stdafx.h"
#include "StageManager.h"

#include "Player.h"

#include "EasyStage.h"
#include "NormalStage.h"
#include "HardStage.h"
#include "BossStage.h"

/*====================================================================
	초기화에서 플래이어를 만들어 주며, 첫 스테이지를 설정합니다.
	기본 값은 EASY이며, 실험하고 싶은 스테이지로 설정하면 해당 스테이지로 세팅됩니다.
====================================================================*/
HRESULT StageManager::init()
{
	//플래이어 객체 생성
	_player = new Player;
	_player->init();
	_player->setLinkStageM(this);
	EVENT_M->setLinkPlayer(_player);

	//첫 스테이지 세팅
	setStage(STAGETYPE::BOSS);

	return S_OK;
}

/*====================================================================
	Player와 Stage의 메모리를 삭제해 줍니다.
====================================================================*/
void StageManager::release()
{
	_player->release();
	SAFE_DELETE(_player);

	_stage->release();
	SAFE_DELETE(_stage);
}	

/*====================================================================
	Player와 Stage에 대한 걸 업데이트 하며,
	이벤트가 실행 중이지 않을 때에는 카메라가 플래이어를 따라 갑니다.
====================================================================*/
void StageManager::update()
{
	_stage->update();
	_player->update();

	if (!EVENT_M->getIsCameraMove()) CAMERA_M->SetPos(_player->getObj().pos.x, _player->getObj().pos.z, 0, 0, 4.0f);
	// 디버그요오오오오옹(21.01.07 만두루루룸)
	if (KEY_M->isOnceKeyDown(VK_F1)) setStage(STAGETYPE::EASY);
	if (KEY_M->isOnceKeyDown(VK_F2)) setStage(STAGETYPE::NORMAL);
	if (KEY_M->isOnceKeyDown(VK_F3)) setStage(STAGETYPE::HARD);
	if (KEY_M->isOnceKeyDown(VK_F4)) setStage(STAGETYPE::BOSS);
}

/*====================================================================
	Player와 Stage를 렌더 합니다.
====================================================================*/
void StageManager::render()
{
	_stage->render();
	_player->render();
}

/*====================================================================
	setStage 함수는 enum class STAGETYPE을 인자값으로 받아,
	현제 스테이지를 해당 스테이지로 설정 해 줍니다.
====================================================================*/
void StageManager::setStage(STAGETYPE current)
{
	if (_stage != NULL)
	{
		if (_currentStage == current) return;	//현재 스테이지와 같을 경우 스테이지를 바꾸지 않는다.

		_stage->release();		//스테이지가 비어있지 않으면, 바꾸기 전에
		SAFE_DELETE(_stage);	//메모리를 날려 주고 딜리트 해 준다.
	}

	_preStage = _currentStage;
	_currentStage = current;	//현재 스테이지를 바꿔 준다.

	//새로운 스테이지 객체를 생성하고, 초기화한다.
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

	//플래이어가 스테이지 초기화를 한다.
	_player->stageInit();
}
