#include "stdafx.h"
#include "GameScene.h"

#include "StageManager.h"


HRESULT GameScene::init()
{
	/*====================================================================
		게임 씬은 스테이지 매니저를 가집니다.
	====================================================================*/
	_stageM = new StageManager;
	_stageM->init();

	return S_OK;
}

void GameScene::release()
{
	_stageM->release();
	SAFE_DELETE(_stageM);
}

void GameScene::update()
{
	_stageM->update();

}

void GameScene::render()
{
	/*====================================================================
		스테이지 매니저를 렌더 시키고, Z-Order에 따라 정렬해 렌더합니다.
	====================================================================*/
	_stageM->render();
	ZORDER_M->render();
}
