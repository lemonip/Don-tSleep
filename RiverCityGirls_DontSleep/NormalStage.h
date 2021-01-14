#pragma once
#include "Stage.h"
#include "StageManager.h"
class NormalStage : public Stage
{

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

