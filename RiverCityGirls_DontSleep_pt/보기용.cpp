#include "stdafx.h"
#include "CollisionManager.h"

#include "StageManager.h"
#include "Stage.h"
#include "Player.h"

HRESULT CollisionManager::init()
{
	return S_OK;
}

void CollisionManager::release()
{
}

void CollisionManager::LRUDCollision(GameObject* character, GameObject* obj)
{
	vector3 interVector; // �������� ���� ����
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
					character->pos.z = obj->bottomPlane[2].getEnd().z + character->shadow.height / 2;
				}
			}
		}
		else if (obj->bottomPlane[3].getEnd().z < character->shadow.RB.z &&
			character->shadow.RT.z < obj->bottomPlane[3].getStart().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
		{
			if (obj->dir == DIRECTION::LEFT)
			{
				if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector) ||
					Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector)) // ���� ������ �����ϸ�
				{
					if (character->shadow.LT.x < interVector.x)
					{
						character->pos.x = interVector.x + character->shadow.width / 2; // ���� ������ ���������� ����
					}
				}
			}
			else if (obj->dir == DIRECTION::RIGHT)
			{
				if (Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[3], &interVector) ||
					Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector)) // ���� ������ ���� ���а� �����ϸ�
				{
					if (character->shadow.RT.x > interVector.x)
					{
						character->pos.x = interVector.x - character->shadow.width / 2; // ���� ������ �������� ����
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
					}
				}
			}
			else if (obj->dir == DIRECTION::RIGHT)
			{
				if (Linear(character->shadow.LB, character->shadow.RB).segmentIntersect(obj->bottomPlane[1], &interVector) ||
					Linear(character->shadow.LT, character->shadow.RT).segmentIntersect(obj->bottomPlane[1], &interVector)) // �غ� ������ �������̶� �����ϸ�
				{
					if (interVector.x > character->shadow.LB.x)
					{
						character->pos.x = interVector.x + character->shadow.width / 2; // ���� ������ ���������� ����
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
		if (obj->bottomPlane[1].getStart().z < character->shadow.LB.z &&
			character->shadow.LT.z < obj->bottomPlane[1].getEnd().z) // Object�� z ���� �ȿ� ���� �� (���� ������)
		{
			if (obj->dir == DIRECTION::LEFT)
			{
				if (character->preShadow.RB.z < obj->bottomPlane[2].getStart().z)
				{
					vector3 tempV;
					if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[2], &tempV)) // �������� �غ��� ������ ��(1�� ����)
					{
						character->pos.x = obj->bottomPlane[2].getStart().x + character->shadow.width / 2;
					}
				}

				if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // ���� ������ �������̶� �����ϸ�
					Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[0], &interVector))	   // ���� ������ �����̶� �����ϸ� 
				{
					if (obj->bottomPlane[1].getStart().z < character->shadow.LT.z) // �׸��� ������ ������Ʈ �������� �Ʒ��� ���� ���
					{
						character->pos.x = obj->bottomPlane[1].getX(character->shadow.LT.z) + character->shadow.width / 2; // ���� ������ �������� ����
					}
					else // �׸��� ������ ������Ʈ �������� ���� ���� ���
					{
						if (character->preShadow.LB.z == character->shadow.LB.z)
						{
							character->pos.x = obj->bottomPlane[1].getStart().x + character->shadow.width / 2;
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
					}
				}

				if (Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[1], &interVector) ||  // ���� ������ �������̶� �����ϸ�
					Linear(character->shadow.LT, character->shadow.LB).segmentIntersect(obj->bottomPlane[2], &interVector))	   // ���� ������ �غ��̶� �����ϸ� 
				{
					if (character->shadow.LB.z < obj->bottomPlane[2].getStart().z) // �׸��� �غ��� ������Ʈ �غ����� ���� ���� ���
					{
						character->pos.x = obj->bottomPlane[1].getX(character->shadow.LB.z) + character->shadow.width / 2; // ���� ������ �������� ����
					}
					else // �׸��� �غ��� ������Ʈ �غ����� �Ʒ��� ���� ���
					{
						if (character->preShadow.LB.z == character->shadow.LB.z)
						{
							character->pos.x = obj->bottomPlane[1].getEnd().x + character->shadow.width / 2;
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
				if (character->preShadow.RT.z > obj->bottomPlane[0].getEnd().z)
				{
					vector3 tempV;
					if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[0], &tempV)) // ���� ������ ������Ʈ�� ������ ��ġ��(1������)
					{
						character->pos.x = obj->bottomPlane[0].getStart().x - character->shadow.width / 2;
					}
				}

				if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // ���� ������ �������̶� �����ϸ�
					Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[2], &interVector))		// ���� ������ �غ��̶� �����ϸ�
				{
					if (character->shadow.RB.z < obj->bottomPlane[2].getEnd().z) // �׸��� �غ��� ������Ʈ �غ����� ���� ���� ���
					{
						character->pos.x = obj->bottomPlane[3].getX(character->shadow.RB.z) - character->shadow.width / 2; // ���� ������ �������� ����
					}
					else // �׸��� �غ��� ������Ʈ �غ����� �Ʒ��� ���� ���
					{
						character->pos.x = obj->bottomPlane[3].getStart().x - character->shadow.width / 2;
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
					}
				}
				if (Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[3], &interVector) || // ���� ������ �������̶� �����ϸ�
					Linear(character->shadow.RT, character->shadow.RB).segmentIntersect(obj->bottomPlane[0], &interVector))		// ���� ������ �����̶� �����ϸ�
				{
					if (character->shadow.RT.z > obj->bottomPlane[0].getStart().z) // �׸��� ������ ������Ʈ �������� �ؿ� ���� ���
					{
						character->pos.x = obj->bottomPlane[3].getX(character->shadow.RT.z) - character->shadow.width / 2; // ���� ������ �������� ����
					}
					else // �׸��� ������ ������Ʈ �������� ���� ���� ���
					{

							character->pos.x = obj->bottomPlane[3].getEnd().x - character->shadow.width / 2;
						
					}
				}
			}
		}
	}
}

void CollisionManager::objectCollision()
{
	wallCollsion();
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
				// ������Ʈ�� ��ġ��
				if (obj->bottomPlane[0].getStart().z < character->shadow.LB.z &&					// ĳ������ z���� �������� �ؿ� �ְ�
					character->shadow.LT.z < obj->bottomPlane[2].getStart().z &&					// ĳ������ z���� �غ����� ���� �ְ�
					obj->bottomPlane[3].getX(character->shadow.RB.z) < character->shadow.RB.x &&	// ĳ������ x���� ���������� ������ �ְ�
					character->shadow.LT.x < obj->bottomPlane[1].getX(character->shadow.LT.z))		// ĳ������ x���� ���������� ������ �ְ�
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
							_stageM->getPlayer()->setState(_stageM->getPlayer()->getInfo().preState);
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
				// ������Ʈ�� �Ȱ������� (�ʿ��Ѱ�?)
				else
				{
					if (obj->topPlane[0].getStart().y < character->pos.y) // ������Ʈ ���̺��� ������ �浹ó��
					{
						LRUDCollision(character, obj);
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

						}
					}
				}
			}
		}
	}
}

void CollisionManager::wallCollsion()
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

}
