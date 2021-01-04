#pragma once
#include "Enemy.h"
class Boss : public Enemy
{
private:

public:

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();
};

