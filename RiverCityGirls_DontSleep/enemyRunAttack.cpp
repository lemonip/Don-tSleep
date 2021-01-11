#include "stdafx.h"
#include "enemyRunAttack.h"
#include "Enemy.h"

void enemyRunAttack::EnterState()
{
	_thisEn->SetImage();
}

void enemyRunAttack::UpdateState()
{

	LookAtPlayer();

	Attack();


}

void enemyRunAttack::ExitState()
{
	_thisEn->getInfo().isAttack = false;

}
