#include "stdafx.h"
#include "enemyRunAttack.h"
#include "Enemy.h"

void enemyRunAttack::EnterState()
{
	_thisEn->SetImage();
	LookAtPlayer();
}

void enemyRunAttack::UpdateState()
{

	Attack();


}

void enemyRunAttack::ExitState()
{
	_thisEn->getInfo().isAttack = false;

}
