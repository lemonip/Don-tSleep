#include "stdafx.h"
#include "BossStage.h"
#include "Enemy.h"

HRESULT BossStage::init()
{
	Stage::init();

	/*====================================================================
		���������� ��� �̹����� �����ϰ�, ī�޶󿡰� �� ����� �˷� �ݴϴ�.
	====================================================================*/
	backGround = IMG_M->findImage("bossStage");
	CAMERA_M->SetMap(*this, backGround);

	/*====================================================================
		���������� ���� ��ġ�մϴ�. LT, RT, RB, LB ��!!
	====================================================================*/
	backWallInit(vector3(650, 9999, 0), vector3(2480, 9999, 0), vector3(2480, 0, 535), vector3(650, 0, 535));

	leftWallInit(vector3(0, 9999, 0), vector3(650, 9999, 0), vector3(650, 0, 535), vector3(0, 0, 1180));

	rightWallInit(vector3(2480, 9999, 0), vector3(3116, 9999, 0), vector3(3116, 0, 1160), vector3(2480, 0, 535));

	floorInit(vector3(0, 0, 1180), vector3(3116, 0, 1160), vector3(3116, 0, 1215), vector3(0, 0, 1215));

	/*====================================================================
		������Ʈ�� ���ʹ̸� ��ġ�մϴ�.
	====================================================================*/
	_objectM->pushObject(OBJECT_TYPE::PILLAR_LEFT, vector3(1000, 0, 700));
	_objectM->pushObject(OBJECT_TYPE::PILLAR_BIG_LEFT, vector3(700, 0, 1000));
	_objectM->pushObject(OBJECT_TYPE::PILLAR_RIGHT, vector3(2100, 0, 700));
	_objectM->pushObject(OBJECT_TYPE::PILLAR_BIG_RIGHT, vector3(2416, 0, 1000));
	_objectM->particleInit(vector3(970, 0, 700), OBJECT_TYPE::PILLAR_LEFT);
	_objectM->particleInit(vector3(670, 0, 1000), OBJECT_TYPE::PILLAR_BIG_LEFT);
	_objectM->particleInit(vector3(2070, 0, 700), OBJECT_TYPE::PILLAR_RIGHT);
	_objectM->particleInit(vector3(2386, 0, 1000), OBJECT_TYPE::PILLAR_BIG_RIGHT);

	_enemyM->pushEnemy(ENEMY_TYPE::BOSS, vector3(WINSIZEX , 0, WINSIZEY - 20));
	
	/*====================================================================
		�������� ���� �� ���� �� �̺�Ʈ�� �߰��մϴ�.
	====================================================================*/
	//EVENT_M->addEvent(new moviePlay(VIDEOTYPE::BOSS_INTRO));
	//EVENT_M->addEvent(new dialogue(DIALOGLIST::BOSS_START), false);
	////EVENT_M->addEvent(new dialogue(DIALOGLIST::BOSS_END), false);

	/*====================================================================
		UI ���� ü�� �ٸ� ȣ���Ѵ�.
	====================================================================*/
	UI_M->addBar("bossHPBar", IMG_M->findImage("bossHPFront"), IMG_M->findImage("bossHPBack"), vector3(200, 580, 0),
		&_enemyM->getVEnemy()[0]->getInfo().hp, &_enemyM->getVEnemy()[0]->getInfo().maxHp);
	UI_M->findUI("bossHPBar")->setActive(true);
	//if (_enemyM->getVEnemy().empty()) UI_M->findUI("bossHPBar")->setActive(false);

	return S_OK;
}

void BossStage::release()
{
	Stage::release();
}

void BossStage::update()
{
	Stage::update();
}

void BossStage::render()
{
	Stage::render();
}
