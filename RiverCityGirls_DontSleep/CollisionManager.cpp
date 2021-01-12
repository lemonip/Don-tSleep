#include "stdafx.h"
#include "CollisionManager.h"

#include "StageManager.h"
#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

HRESULT CollisionManager::init()
{
	return S_OK;
}

void CollisionManager::release()
{
}

void CollisionManager::LRUDCollision(GameObject* character, GameObject* obj)
{
	checkLeft = checkRight = checkUp = checkDown = false;
	vector3 interVector; // �������� ���� ����
	if (obj->bottomPlane[0].getStart().y == 0)
	{
	/*====================================================================
								�� / �Ʒ� �浹
	====================================================================*/
	//==================================��==================================//
		if (character->prePos.z > character->pos.z) // �÷��̾ �������� �������� ��
		{
			if (obj->bottomPlane[2].getEnd().x < character->shadow.RT.x &&
				character->shadow.LT.x < obj->bottomPlane[2].getStart().x) // ������Ʈ�� x ���� �ȿ� ������ ��
			{
				if (character->shadow.RT.z < obj->bottomPlane[2].getEnd().z &&
					obj->bottomPlane[2].getEnd().z < character->shadow.RB.z) // ������ ������Ʈ�� �ظ��� �Ѿ��
				{
					if (character->preShadow.LT.z >= obj->bottomPlane[2].getStart().z) // �ؿ��� ���� �ö󰣰Ÿ�
					{
						if (obj->type == OBJECT_TYPE::LADDER)
						{
							if (obj->bottomPlane[2].getEnd().x < character->pos.x &&
								character->pos.x < obj->bottomPlane[2].getStart().x &&
								(GetAsyncKeyState(VK_UP) & 0x8001))
							{
								_stageM->getPlayer()->setIsClimb(true);
							}
							if (!(_stageM->getPlayer()->getInfo().isClimb))
							{
								character->pos.z = obj->bottomPlane[2].getEnd().z + character->shadow.height / 2;
							}
						}
						else
						{
							character->pos.z = obj->bottomPlane[2].getEnd().z + character->shadow.height / 2;
							checkUp = true;
						}
					}
				}
			}
			else if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
				character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector) ||
						Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector)) // ����,�غ� ������ ���� ���а� �����ϸ�
					{
						if (character->shadow.LT.x < interVector.x)
						{
							character->pos.x = interVector.x + character->shadow.width / 2; // ���� ������ ���������� ����
							checkUp = true;
						}
					}
				}
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[3], &interVector) ||
						Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector)) // ����, �غ� ������ ���� ���а� �����ϸ�
					{
						if (character->shadow.RT.x > interVector.x)
						{
							character->pos.x = interVector.x - character->shadow.width / 2; // ���� ������ �������� ����
							checkUp = true;
						}
					}
				}
			}
		}
		//==================================�Ʒ�==================================//
		else if (character->prePos.z < character->pos.z) // �÷��̾ �Ʒ��� �������� ��
		{
			if (obj->bottomPlane[0].getStart().x < character->shadow.RB.x &&
				character->shadow.LB.x < obj->bottomPlane[0].getEnd().x) // ������Ʈ�� x ���� �ȿ� ������ ��
			{
				if (character->shadow.LT.z < obj->bottomPlane[0].getStart().z &&
					obj->bottomPlane[0].getStart().z < character->shadow.LB.z) // �غ��� ������Ʈ�� ������ �Ѿ��
				{
					if (character->preShadow.LB.z <= obj->bottomPlane[0].getStart().z)	// ������ �Ʒ��� ��������
					{
						character->pos.z = obj->bottomPlane[0].getStart().z - character->shadow.height / 2;
						checkDown = true;
					}
				}
			}
			else if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
				character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) ||
						Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[3], &interVector)) // �غ� ������ �������̶� �����ϸ�
					{
						if (interVector.x < character->shadow.RB.x)
						{
							character->pos.x = interVector.x - character->shadow.width / 2; // ���� ������ �������� ����
							checkDown = true;
						}
					}
				}
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector) ||
						Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector)) // �غ� ������ �������̶� �����ϸ�
					{
						if (character->shadow.LB.x < interVector.x)
						{
							character->pos.x = interVector.x + character->shadow.width / 2; // ���� ������ ���������� ����
							checkDown = true;
						}
					}
				}
			}
		}
		/*====================================================================
									�� / �� �浹
		====================================================================*/
		//==================================��==================================//
		if (character->prePos.x > character->pos.x) // �÷��̾ �������� �������� ��
		{
			if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&
				character->shadow.LT.z < obj->bottomPlane[2].getEnd().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (character->preShadow.LT.z < obj->bottomPlane[2].getStart().z)
					{
						vector3 tempV;
						if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[2], &tempV)) // �������� �غ��� ������ ��(1�� ����)
						{
							character->pos.x = obj->bottomPlane[2].getStart().x + character->shadow.width / 2;
							checkLeft = true;
						}
					}

					if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // ���� ������ �������̶� �����ϸ�
						Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[0], &interVector))	   // ���� ������ �����̶� �����ϸ� 
					{
						if (obj->bottomPlane[0].getEnd().z < character->shadow.LT.z) // �׸��� ������ ������Ʈ �������� �Ʒ��� ���� ���
						{
							character->pos.x = obj->bottomPlane[1].getX(character->shadow.LT.z) + character->shadow.width / 2; // ���� ������ �������� ����
							checkLeft = true;
						}
						else // �׸��� ������ ������Ʈ �������� ���� ���� ���
						{
							if (character->preShadow.LB.z > obj->bottomPlane[0].getEnd().z)
							{
								character->pos.x = obj->bottomPlane[1].getStart().x + character->shadow.width / 2;
								checkLeft = true;
							}
						}
					}
				}
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (character->preShadow.LB.z > obj->bottomPlane[0].getStart().z)
					{
						vector3 tempV;
						if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[0], &tempV)) // �������� ������ ������ ��(1�� ����)
						{
							character->pos.x = obj->bottomPlane[0].getEnd().x + character->shadow.width / 2;
							checkLeft = true;
						}
					}

					if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // ���� ������ �������̶� �����ϸ�
						Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[2], &interVector))	   // ���� ������ �غ��̶� �����ϸ� 
					{
						if (obj->bottomPlane[2].getStart().z > character->shadow.LB.z) // �׸��� �غ��� ������Ʈ �غ����� ���� ���� ���
						{
							character->pos.x = obj->bottomPlane[1].getX(character->shadow.LB.z) + character->shadow.width / 2; // ���� ������ �������� ����
							checkLeft = true;
						}
						else // �׸��� �غ��� ������Ʈ �غ����� �Ʒ��� ���� ���
						{
							if (character->preShadow.LT.z < obj->bottomPlane[2].getStart().z)
							{
								character->pos.x = obj->bottomPlane[1].getEnd().x + character->shadow.width / 2;
								checkLeft = true;
							}
						}
					}
				}
			}
		}
		//==================================��==================================//
		else if (character->prePos.x < character->pos.x) // �÷��̾ ���������� �������� ��
		{
			if (obj->bottomPlane[0].getStart().z < character->shadow.RB.z &&
				character->shadow.RT.z < obj->bottomPlane[2].getEnd().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (character->preShadow.RB.z > obj->bottomPlane[0].getStart().z)
					{
						vector3 tempV;
						if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[0], &tempV)) // ���� ������ ������Ʈ�� ������ ��ġ��(1������)
						{
							character->pos.x = obj->bottomPlane[0].getStart().x - character->shadow.width / 2;
							checkRight = true;
						}
					}
					if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) ||	// ���� ������ �������̶� �����ϸ�
						Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[2], &interVector))		// ���� ������ �غ��̶� �����ϸ�
					{
						if (character->shadow.RB.z < obj->bottomPlane[2].getEnd().z) // �׸��� �غ��� ������Ʈ �غ����� ���� ���� ���
						{
							character->pos.x = obj->bottomPlane[3].getX(character->shadow.RB.z) - character->shadow.width / 2; // ���� ������ �������� ����
							checkRight = true;
						}
						else // �׸��� �غ��� ������Ʈ �غ����� �Ʒ��� ���� ���
						{
							if (character->preShadow.RT.z < obj->bottomPlane[2].getEnd().z)
							{
								character->pos.x = obj->bottomPlane[3].getStart().x - character->shadow.width / 2;
								checkRight = true;
							}
						}
					}
				}
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (character->preShadow.RT.z < obj->bottomPlane[2].getStart().z)
					{
						vector3 tempV;
						if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[2], &tempV)) // ���� ������ ������Ʈ�� �غ��� ��ġ��(1������)
						{
							character->pos.x = obj->bottomPlane[2].getEnd().x - character->shadow.width / 2;
							checkRight = true;
						}
					}
					if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // ���� ������ �������̶� �����ϸ�
						Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[0], &interVector))		// ���� ������ �����̶� �����ϸ�
					{
						if (character->shadow.RT.z > obj->bottomPlane[0].getStart().z) // �׸��� ������ ������Ʈ �������� �ؿ� ���� ���
						{
							character->pos.x = obj->bottomPlane[3].getX(character->shadow.RT.z) - character->shadow.width / 2; // ���� ������ �������� ����
							checkRight = true;
						}
						else // �׸��� ������ ������Ʈ �������� ���� ���� ���
						{
							if (character->preShadow.RT.z > obj->bottomPlane[0].getStart().z)
							{
								character->pos.x = obj->bottomPlane[3].getEnd().x - character->shadow.width / 2;
								checkRight = true;
							}
						}
					}
				}
			}
		}
	}
	if (checkUp || checkDown || checkLeft || checkRight)
	{
		character->obstacle = obj;
	}

	// ������� �浹
	if (_stageM->getCurStage() == STAGETYPE::HARD)
	{
		vector3 temp;
		tagWall pool = _stageM->getStage()->getPool();
		if (pool.LT.x < character->shadow.RB.x &&
			character->shadow.LB.x < pool.RT.x)  // �÷��̾� �Ʒ��� �ִ�ġ (������ �浹)
		{
			if (character->shadow.LB.z > pool.RT.z)
			{
				character->pos.z = pool.RT.z - character->shadow.height / 2;
			}
		}
		if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(Linear(pool.RT, pool.RB), &temp))  // �������� �����ʰ� �浹 ��
		{
			character->pos.x = Linear(pool.RT, pool.RB).getX(character->shadow.LB.z) + character->shadow.width / 2;
		}
	}
}

void CollisionManager::playerWallCollsion()
{
	GameObject* character = _stageM->getPlayer()->getPObj();
	vector<tagWall> vLeftWall = _stageM->getStage()->getLeftWall();
	vector<tagWall> vRightWall = _stageM->getStage()->getRightWall();
	vector<tagWall> vBackWall = _stageM->getStage()->getBackWall();
	tagWall floor = _stageM->getStage()->getFloor();

	vector3 interVector;
	for (int i = 0; i < vBackWall.size(); ++i) // �÷��̾� ���� �ִ�ġ (�� �� �浹)
	{
		if (character->shadow.LT.z < vBackWall[i].LB.z)
		{
			if (character->shadow.RT.x > vBackWall[i].LB.x &&
				character->shadow.LT.x < vBackWall[i].RB.x)
			{
				character->pos.z = vBackWall[i].LB.z + character->shadow.height / 2;
			}
		}
	}

	for (int i = 0; i < vLeftWall.size(); ++i)
	{
		if (character->preShadow.LT.z < vLeftWall[i].LB.z)
		{
			if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(vLeftWall[i].RB, vLeftWall[i].LB), &interVector))  // �׸��� ������ ���� ���̶� �����ϸ�
			{
				character->pos.x = interVector.x + character->shadow.width / 2;
			}
		}
	}

	for (int i = 0; i < vRightWall.size(); ++i)
	{
		if (character->preShadow.RT.z < vRightWall[i].RB.z)
		{
			if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(vRightWall[i].LB, vRightWall[i].RB), &interVector))  // �׸��� ������ ������ ���̶� �����ϸ�
			{
				character->pos.x = interVector.x - character->shadow.width / 2;
			}
		}
	}

	// �ٴڰ� �浹
	if (character->shadow.LB.z > floor.LB.z) // �÷��̾� �Ʒ��� �ִ�ġ (�ٴ� �浹)
	{
		character->pos.z = floor.LB.z - character->shadow.height / 2;
	}
	if (character->shadow.LB.x < floor.LT.x) // �ٴ� ����
	{
		character->pos.x = floor.LT.x + character->shadow.width / 2;
	}
	if (character->shadow.RB.x > floor.RT.x) // �ٴ� ������
	{
		character->pos.x = floor.RT.x - character->shadow.width / 2;
	}

	// ������� �浹
	if (_stageM->getCurStage() == STAGETYPE::HARD)
	{
		vector3 temp;
		tagWall pool = _stageM->getStage()->getPool();
		if (pool.LT.x < character->shadow.RB.x &&
			character->shadow.LB.x < pool.RT.x)  // �÷��̾� �Ʒ��� �ִ�ġ (������ �浹)
		{
			if (character->shadow.LB.z > pool.RT.z)
			{
				character->pos.z = pool.RT.z - character->shadow.height / 2;
			}
		}
		if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(Linear(pool.RT, pool.RB), &temp))  // �������� �����ʰ� �浹 ��
		{
			character->pos.x = Linear(pool.RT, pool.RB).getX(character->shadow.LB.z) + character->shadow.width / 2;
		}
	}
}

void CollisionManager::enemyWallColiision(GameObject* character)
{
	vector<tagWall> vLeftWall = _stageM->getStage()->getLeftWall();
	vector<tagWall> vRightWall = _stageM->getStage()->getRightWall();
	vector<tagWall> vBackWall = _stageM->getStage()->getBackWall();
	tagWall floor = _stageM->getStage()->getFloor();

	vector3 interVector;
	for (int i = 0; i < vBackWall.size(); ++i) // �÷��̾� ���� �ִ�ġ (�� �� �浹)
	{
		if (character->shadow.LT.z < vBackWall[i].LB.z)
		{
			if (character->shadow.RT.x > vBackWall[i].LB.x &&
				character->shadow.LT.x < vBackWall[i].RB.x)
			{
				character->pos.z = vBackWall[i].LB.z + character->shadow.height / 2;
			}
		}
	}

	for (int i = 0; i < vLeftWall.size(); ++i)
	{
		if (character->preShadow.LT.z < vLeftWall[i].LB.z)
		{
			if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(vLeftWall[i].RB, vLeftWall[i].LB), &interVector))  // �׸��� ������ ���� ���̶� �����ϸ�
			{
				character->pos.x = interVector.x + character->shadow.width / 2;
			}
		}
	}

	for (int i = 0; i < vRightWall.size(); ++i)
	{
		if (character->preShadow.RT.z < vRightWall[i].RB.z)
		{
			if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(Linear(vRightWall[i].LB, vRightWall[i].RB), &interVector))  // �׸��� ������ ������ ���̶� �����ϸ�
			{
				character->pos.x = interVector.x - character->shadow.width / 2;
			}
		}
	}

	// �ٴڰ� �浹
	if (character->shadow.LB.z > floor.LB.z) // �÷��̾� �Ʒ��� �ִ�ġ (�ٴ� �浹)
	{
		character->pos.z = floor.LB.z - character->shadow.height / 2;
	}
	if (character->shadow.LB.x < floor.LT.x) // �ٴ� ����
	{
		character->pos.x = floor.LT.x + character->shadow.width / 2;
	}
	if (character->shadow.RB.x > floor.RT.x) // �ٴ� ������
	{
		character->pos.x = floor.RT.x - character->shadow.width / 2;
	}

	// ������� �浹
	if (_stageM->getCurStage() == STAGETYPE::HARD)
	{
		vector3 temp;
		tagWall pool = _stageM->getStage()->getPool();
		if (pool.LT.x < character->shadow.RB.x &&
			character->shadow.LB.x < pool.RT.x)  // �÷��̾� �Ʒ��� �ִ�ġ (������ �浹)
		{
			if (character->shadow.LB.z > pool.RT.z)
			{
				character->pos.z = pool.RT.z - character->shadow.height / 2;
			}
		}
		if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(Linear(pool.RT, pool.RB), &temp))  // �������� �����ʰ� �浹 ��
		{
			character->pos.x = Linear(pool.RT, pool.RB).getX(character->shadow.LB.z) + character->shadow.width / 2;
		}
	}
}


void CollisionManager::playerObjectCollision()
{
	playerWallCollsion();
	GameObject* character = _stageM->getPlayer()->getPObj();
	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();
	if (character->pos.y > 0) character->pos.y = 0;
	for (int i = 0; i < vObj.size(); ++i)
	{
		GameObject* obj = vObj[i]->getObj();

		if (obj->group == OBJECT_GROUP::OBJECT)
		{
			if (_stageM->getPlayer()->getInfo().isSky) // ���߿� ���� ��
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// ĳ������ z���� �������� �ؿ� �ְ�
						character->shadow.LT.z < obj->bottomPlane[2].getStart().z)						// ĳ������ z���� �غ����� ���� �ְ�
					{
						float tempMaxUz = obj->bottomPlane[1].getX(character->shadow.LT.z);				// ������Ʈ ���� �ִ밪
						if (obj->bottomPlane[1].getStart().x < tempMaxUz) tempMaxUz = obj->bottomPlane[1].getStart().x;
						float tempMaxDz = obj->bottomPlane[3].getX(character->shadow.RB.z);
						if (tempMaxDz < obj->bottomPlane[3].getStart().x) tempMaxDz = obj->bottomPlane[3].getStart().x;

						if (tempMaxDz < character->shadow.RB.x &&
							character->shadow.LT.x < tempMaxUz)											// �ƽ����麸�� ���̿� ������
						{
							if (character->prePos.y < character->pos.y) // ���� ���� ��
							{
								if (obj->topPlane[0].getStart().y - 5 < character->pos.y &&
									character->pos.y <= obj->topPlane[0].getStart().y + 5) // �ش� ������ ����
								{
									// y�� ����
									character->pos.y = obj->topPlane[0].getStart().y;
									// ���º���
									_stageM->getPlayer()->setPlatform(obj);
									_stageM->getPlayer()->setState(PL_STATE::IDLE);
									_stageM->getPlayer()->setJumpPower(0);
									_stageM->getPlayer()->setIsSky(false);
								}
								else if (character->pos.y > obj->topPlane[0].getStart().y + 5) // ���� �� ������Ʈ ���̺��� ���� ��
								{
									LRUDCollision(character, obj);
								}
							}
							else if (character->pos.y < character->prePos.y) // ���� ���� �� 
							{
								if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
								{
									LRUDCollision(character, obj);
								}
							}
						}
					}
					// ������Ʈ�� �Ȱ������� (�ʿ��Ѱ�?)
					else
					{
						if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
						{
							LRUDCollision(character, obj);
						}
					}
				}
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// ĳ������ z���� �������� �ؿ� �ְ�
						character->shadow.LT.z < obj->bottomPlane[2].getStart().z)						// ĳ������ z���� �غ����� ���� �ְ�
					{
						float tempMaxUz = obj->bottomPlane[3].getX(character->shadow.RT.z);				// ������Ʈ ���� �ִ밪
						if (tempMaxUz < obj->bottomPlane[3].getEnd().x) tempMaxUz = obj->bottomPlane[3].getEnd().x;
						float tempMaxDz = obj->bottomPlane[1].getX(character->shadow.LB.z);
						if (obj->bottomPlane[1].getEnd().x < tempMaxDz) tempMaxDz = obj->bottomPlane[1].getEnd().x;
						
						if (character->shadow.LB.x < tempMaxDz &&
							tempMaxUz < character->shadow.RT.x)
						{
							if (character->prePos.y < character->pos.y) // ���� ���� ��
							{
								if (obj->topPlane[0].getStart().y - 5 < character->pos.y &&
									character->pos.y <= obj->topPlane[0].getStart().y + 5) // �ش� ������ ����
								{
									
									// y�� ����
									character->pos.y = obj->topPlane[0].getStart().y;
									// ���º���
									_stageM->getPlayer()->setPlatform(obj);
									_stageM->getPlayer()->setState(PL_STATE::IDLE);
									_stageM->getPlayer()->setJumpPower(0);
									_stageM->getPlayer()->setIsSky(false);
								}
								else if (character->pos.y > obj->topPlane[0].getStart().y + 5) // ���� �� ������Ʈ ���̺��� ���� ��
								{
									LRUDCollision(character, obj);
								}
							}
							else if (character->pos.y < character->prePos.y) // ���� ���� �� 
							{
								if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
								{
									LRUDCollision(character, obj);
								}
							}
						}
					}
					// ������Ʈ�� �Ȱ������� (�ʿ��Ѱ�?)
					else
					{
						if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
						{
							LRUDCollision(character, obj);
						}
					}
				}
			}
			else // ������ �ƴ� ��(isSky == false)
			{
				if (character->pos.y == 0) // ������ ��
				{
					LRUDCollision(character, obj);
				}
				else // ������ �ƴ� ��(������Ʈ ���� ��)
				{
					if (_stageM->getPlayer()->getPlatform() != nullptr)
					{
						if (_stageM->getPlayer()->getPlatform()->bottomPlane[0].getStart().z > character->shadow.LB.z ||					// �����
							character->shadow.LT.z > _stageM->getPlayer()->getPlatform()->bottomPlane[2].getStart().z ||					// �����
							_stageM->getPlayer()->getPlatform()->bottomPlane[3].getX(character->shadow.RB.z) > character->shadow.RB.x ||	// �����
							character->shadow.LT.x > _stageM->getPlayer()->getPlatform()->bottomPlane[1].getX(character->shadow.LT.z) ||	// �����
							character->shadow.LT.x > _stageM->getPlayer()->getPlatform()->bottomPlane[0].getEnd().x ||						// �����
							character->shadow.RB.x < _stageM->getPlayer()->getPlatform()->bottomPlane[2].getEnd().x)						// �����
						{
							_stageM->getPlayer()->setState(PL_STATE::JUMP);
							_stageM->getPlayer()->setIsSky(true);
							_stageM->getPlayer()->setJumpPower(0);
						}
					}
				}
			}
		}
	}
}

void CollisionManager::enemyObjectCollision(Enemy* enemy)
{
	GameObject* character = enemy->getObj();
	enemyWallColiision(character);
	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();

	if (character->pos.y > 0) character->pos.y = 0;
	for (int i = 0; i < vObj.size(); ++i)
	{
		GameObject* obj = vObj[i]->getObj();
		if (obj->group == OBJECT_GROUP::OBJECT)
		{
			if (enemy->getInfo().isSky) // ���߿� ���� ��
			{
				if (obj->dir == DIRECTION::LEFT)
				{
					if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// ĳ������ z���� �������� �ؿ� �ְ�
						character->shadow.LT.z < obj->bottomPlane[2].getStart().z)						// ĳ������ z���� �غ����� ���� �ְ�
					{
						float tempMaxUz = obj->bottomPlane[1].getX(character->shadow.LT.z);				// ������Ʈ ���� �ִ밪
						if (obj->bottomPlane[1].getStart().x < tempMaxUz) tempMaxUz = obj->bottomPlane[1].getStart().x;
						float tempMaxDz = obj->bottomPlane[3].getX(character->shadow.RB.z);
						if (tempMaxDz < obj->bottomPlane[3].getStart().x) tempMaxDz = obj->bottomPlane[3].getStart().x;

						if (tempMaxDz < character->shadow.RB.x &&
							character->shadow.LT.x < tempMaxUz)											// �ƽ����麸�� ���̿� ������
						{
							if (character->prePos.y < character->pos.y) // ���� ���� ��
							{
								if (obj->topPlane[0].getStart().y - 5 < character->pos.y &&
									character->pos.y <= obj->topPlane[0].getStart().y + 5) // �ش� ������ ����
								{
									if (enemy->getEnemyType() == ENEMY_TYPE::CHEERLEADER ||
										enemy->getEnemyType() == ENEMY_TYPE::SCHOOLBOY ||
										enemy->getEnemyType() == ENEMY_TYPE::SCHOOLGIRL)
									{
										// y�� ����
										character->pos.y = obj->topPlane[0].getStart().y;
										// ���º���
										enemy->setPlatform(obj);
										enemy->SetState(EN_STATE::EN_IDLE);
										enemy->getInfo().jumpPower = 0;
										enemy->getInfo().isSky = false;
									}
								}
								else if (character->pos.y > obj->topPlane[0].getStart().y + 5) // ���� �� ������Ʈ ���̺��� ���� ��
								{
									LRUDCollision(character, obj);
								}
							}
							else if (character->pos.y < character->prePos.y) // ���� ���� �� 
							{
								if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
								{
									LRUDCollision(character, obj);
								}
							}
						}
					}
					// ������Ʈ�� �Ȱ������� (�ʿ��Ѱ�?)
					else
					{
						if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
						{
							LRUDCollision(character, obj);
						}
					}
				}
				else if (obj->dir == DIRECTION::RIGHT)
				{
					if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// ĳ������ z���� �������� �ؿ� �ְ�
						character->shadow.LT.z < obj->bottomPlane[2].getStart().z)						// ĳ������ z���� �غ����� ���� �ְ�
					{
						float tempMaxUz = obj->bottomPlane[3].getX(character->shadow.RT.z);				// ������Ʈ ���� �ִ밪
						if (tempMaxUz < obj->bottomPlane[3].getEnd().x) tempMaxUz = obj->bottomPlane[3].getEnd().x;
						float tempMaxDz = obj->bottomPlane[1].getX(character->shadow.LB.z);
						if (obj->bottomPlane[1].getEnd().x < tempMaxDz) tempMaxDz = obj->bottomPlane[1].getEnd().x;

						if (character->shadow.LB.x < tempMaxDz &&
							tempMaxUz < character->shadow.RT.x)
						{
							if (character->prePos.y < character->pos.y) // ���� ���� ��
							{
								if (obj->topPlane[0].getStart().y - 5 < character->pos.y &&
									character->pos.y <= obj->topPlane[0].getStart().y + 5) // �ش� ������ ����
								{
									if (enemy->getEnemyType() == ENEMY_TYPE::CHEERLEADER ||
										enemy->getEnemyType() == ENEMY_TYPE::SCHOOLBOY ||
										enemy->getEnemyType() == ENEMY_TYPE::SCHOOLGIRL)
									{
										// y�� ����
										character->pos.y = obj->topPlane[0].getStart().y;
										// ���º���
										enemy->setPlatform(obj);
										enemy->SetState(EN_STATE::EN_IDLE);
										enemy->getInfo().jumpPower = 0;
										enemy->getInfo().isSky = false;
									}
								}
								else if (character->pos.y > obj->topPlane[0].getStart().y + 5) // ���� �� ������Ʈ ���̺��� ���� ��
								{
									LRUDCollision(character, obj);
								}
							}
							else if (character->pos.y < character->prePos.y) // ���� ���� �� 
							{
								if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
								{
									LRUDCollision(character, obj);
								}
							}
						}
					}
					// ������Ʈ�� �Ȱ������� (�ʿ��Ѱ�?)
					else
					{
						if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
						{
							LRUDCollision(character, obj);
						}
					}
				}
			}
			else // ������ �ƴ� ��(isSky == false)
			{
				if (character->pos.y == 0) // ������ ��
				{
					LRUDCollision(character, obj);
				}
				else // ������ �ƴ� ��(������Ʈ ���� ��)
				{
					if (enemy->getPlatform() != nullptr)
					{
						if (enemy->getPlatform()->bottomPlane[0].getStart().z > character->shadow.LB.z ||					// �����
							character->shadow.LT.z > enemy->getPlatform()->bottomPlane[2].getStart().z ||					// �����
							enemy->getPlatform()->bottomPlane[3].getX(character->shadow.RB.z) > character->shadow.RB.x ||	// �����
							character->shadow.LT.x > enemy->getPlatform()->bottomPlane[1].getX(character->shadow.LT.z) ||	// �����
							character->shadow.LT.x > enemy->getPlatform()->bottomPlane[0].getEnd().x ||						// �����
							character->shadow.RB.x < enemy->getPlatform()->bottomPlane[2].getEnd().x)						// �����
						{
							enemy->SetState(EN_STATE::EN_JUMP);
							enemy->getInfo().isSky = true;
							enemy->getInfo().jumpPower = 0;
						}
					}
				}
			}
		}
	}
}

void CollisionManager::destructObject()
{

	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();
	if (vObj.empty() == false)
	{
		for (int i = 0; i < vObj.size(); ++i)
		{
			if (vObj[i]->getObj()->type == OBJECT_TYPE::VENDINGMACHINE)
			{
				if (vObj[i]->getObj()->des == OBJECT_DESTRUCTION::BEFOREDESTRUCTION)
				{
					RECT temp;
					if (IntersectRect(&temp, &_player->getInfo().attackRc, &vObj[i]->getObj()->rc))
					{
						vObj[i]->getObj()->destructionCount -= 1;
					}

					if (vObj[i]->getObj()->destructionCount <= 0)
					{
						vObj[i]->getObj()->des = OBJECT_DESTRUCTION::DESTRUCTION;
					}
				}
			}
		}
	}
}

void CollisionManager::bossDestructObject(Enemy* enemy)
{
	vector<Object*> vObj = _stageM->getStage()->getObjectM()->getVObject();
	if (vObj.empty() == false)
	{
		for (int i = 0; i < vObj.size(); ++i)
		{
			if (vObj[i]->getObj()->type == OBJECT_TYPE::PILLAR_BIG_LEFT ||
				vObj[i]->getObj()->type == OBJECT_TYPE::PILLAR_BIG_RIGHT ||
				vObj[i]->getObj()->type == OBJECT_TYPE::PILLAR_LEFT ||
				vObj[i]->getObj()->type == OBJECT_TYPE::PILLAR_RIGHT)
			{
				if (vObj[i]->getObj()->des == OBJECT_DESTRUCTION::BEFOREDESTRUCTION)
				{
					vector3 temp = vector3((enemy->getInfo().rcAttack.right + enemy->getInfo().rcAttack.left) / 2, 0, (enemy->getInfo().rcAttack.bottom + enemy->getInfo().rcAttack.top) / 2);
					if (enemy->getInfo().dest == DIRECTION::LEFT)
					{
						if (vObj[i]->getObj()->bottomPlane[2].getStart().x < temp.x &&
							temp.x < vObj[i]->getObj()->bottomPlane[0].getEnd().x &&
							vObj[i]->getObj()->bottomPlane[0].getStart().z < enemy->getObj()->shadow.LB.z &&
							enemy->getObj()->shadow.LT.z < vObj[i]->getObj()->bottomPlane[2].getStart().z)
						{
							_stageM->getStage()->getObjectM()->particleSwitch(vObj[i]->getObj()->type);
							_stageM->getStage()->getObjectM()->popObject(i);
							cout << "checkLeft" << endl;
							break;
						}
					}
					else if (enemy->getInfo().dest == DIRECTION::RIGHT)
					{
						if (vObj[i]->getObj()->bottomPlane[0].getStart().x < temp.x &&
							temp.x < vObj[i]->getObj()->bottomPlane[2].getEnd().x &&
							vObj[i]->getObj()->bottomPlane[0].getStart().z < enemy->getObj()->shadow.RB.z &&
							enemy->getObj()->shadow.RT.z < vObj[i]->getObj()->bottomPlane[2].getStart().z)
						{
							_stageM->getStage()->getObjectM()->particleSwitch(vObj[i]->getObj()->type);
							_stageM->getStage()->getObjectM()->popObject(i);
							cout << "checkRight" << endl;
							break;
						}
					}



					/*RECT temp2;
					if (IntersectRect(&temp2, &enemy->getInfo().rcAttack, &vObj[i]->getObj()->rc))
					{
						cout << "check" << endl;
						_stageM->getStage()->getObjectM()->popObject(i);
						break;
					}*/
				}
			}
		}
	}
}

