#pragma once
#include "Scene.h"

class StageManager;

/*====================================================================
	게임 씬입니다. 게임 씬은 StageManager를 가집니다.
====================================================================*/

class GameScene : public Scene
{
private:
	StageManager* _stageM;

public:
	GameScene() {}
	~GameScene() {}

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};