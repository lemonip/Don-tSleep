#pragma once
#include "Scene.h"

class StageManager;
class CollisionManager;

/*====================================================================
	게임 씬입니다. 게임 씬은 StageManager를 가집니다.
====================================================================*/

class GameScene : public Scene
{
private:
	StageManager* _stageM;
	CollisionManager* _colM;
public:
	GameScene() {}
	~GameScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};