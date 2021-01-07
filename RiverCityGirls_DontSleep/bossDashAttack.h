#pragma once
#include"IBossState.h"
#define PI 3.14159f

class StageManager;
class Player;
class Boss;

class bossDashAttack :public IBossState
{
private:
	int _count;
	float _angle;
	float _speed;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};