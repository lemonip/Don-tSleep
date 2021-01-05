#include "stdafx.h"
#include "Stage.h"
#include "ObjectManager.h"

/*====================================================================
	스테이지 초기화 시 에너미 매니저와 오브젝트 매니저를 할당하고 초기화합니다.
====================================================================*/
HRESULT Stage::init()
{
	_enemyM = new EnemyManager;
	_enemyM->init();
	_enemyM->setLinkStageM(_stageM);

	_objectM = new ObjectManager;
	_objectM->init();
	return S_OK;
}

void Stage::release()
{
	_enemyM->release();
	SAFE_DELETE(_enemyM);

	_objectM->release();
	SAFE_DELETE(_objectM);
}

void Stage::update()
{
	//_enemyM->update();
	_objectM->update();

}

void Stage::render()
{
	/*====================================================================
		배경과 에너미와 오브젝트를 렌더한다.
	====================================================================*/
	backGround->render(getMapDC(), backGround->getWidth() / 2, backGround->getHeight() / 2);
	_enemyM->render();
	_objectM->render();
}
