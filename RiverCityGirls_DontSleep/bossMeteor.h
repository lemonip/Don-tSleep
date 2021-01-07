#pragma once
#include"IBossState.h"
#define PI 3.14159f

class StageManager;
class Player;
class Boss;

class bossMeteor :public IBossState
{
private:
	float _enterTime;
	float _angle;
	float _speed;
public:

	virtual void EnterState();
	virtual void UpdateState();
	virtual void ExitState();
};
