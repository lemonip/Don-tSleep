#include "stdafx.h"
#include "Player.h"
//�ܺ�
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "Enemy.h"
//����
#include "IPlayerState.h"
#include "playerIdle.h"
#include "playerWait.h"
#include "playerWalk.h"
#include "playerRun.h"
#include "playerJump.h"
#include "playerStick.h"
#include "playerClimb.h"
#include "playerClimbTop.h"
#include "playerPick.h"
#include "playerGrab.h"
#include "playerGuard.h"
#include "playerRoll.h"
#include "playerHit.h"
#include "playerStun.h"
#include "playerStand.h"
#include "playerDown.h"
#include "playerDead.h"
#include "playerThrow.h"
#include "playerStomp.h"
#include "playerCombo1.h"
#include "playerCombo2.h"
#include "playerCombo3.h"
#include "playerSAttack.h"
#include "playerDashAttack.h"
#include "playerDashSAttack.h"
#include "playerJumpAttack.h"
#include "playerSAttackDown.h"

#include "Weapon.h"
//�ʱ�ȭ
HRESULT Player::init()
{
	/*====================================================================
		�÷��̾��� ������Ʈ �ʱ�ȭ�� �⺻ ������ �մϴ�.
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("pl_wait"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2 + 200));

	//�⺻ ���� �ʱ�ȭ
	{
		_obj.ani = new animation;
		_info.jumpPower = 0;
		_info.speed = 4.f;

		_info.hasMember = false;
		_info.hasWeapon = false;
		_info.isImmune = false;
		_info.isAttack = false;
		_info.isHit = false;
		_info.isDead = false;
		_info.isControl = true;
		_info.isConDest = true;
		_info.isSky = false;
		_info.isClimb = false;

		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
		_info.goalState = GOALPOS::PLAYER;

		_info.hp = _info.maxHP = 100;
		_info.force = 10;
		_info.LV = 1;
		_info.exp = 0;
		_info.hitCount = 3;

		_info.frameTimer = TIME_M->getWorldTime();
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		_info.immuneTimer = 0;
	}

	//�������� ���
	{
		_idle = new playerIdle;
		_wait = new playerWait;
		_walk = new playerWalk;
		_run = new playerRun;
		_jump = new playerJump;
		_stick = new playerStick;
		_climb = new playerClimb;
		_climbTop = new playerClimbTop;
		_pick = new playerPick;

		_grab = new playerGrab;
		_guard = new playerGuard;
		_roll = new playerRoll;
		_hit = new playerHit;
		_stun = new playerStun;
		_stand = new playerStand;
		_down = new playerDown;
		_dead = new playerDead;

		_throw = new playerThrow;
		_stomp = new playerStomp;
		_combo1 = new playerCombo1;
		_combo2 = new playerCombo2;
		_combo3 = new playerCombo3;

		_sAttack = new playerSAttack;
		_dashAttack = new playerDashAttack;
		_dashSAttack = new playerDashSAttack;
		_jumpAttack = new playerJumpAttack;
		_SAttackDown = new playerSAttackDown;
	}
	setState(PL_STATE::WAIT);
	return S_OK;
}

void Player::release()
{
}

//���� ���� �߿��ԡ� ����->�߷�->Ű�Է�
void Player::update()
{
	//cout << (int)_info.state<< endl;

	_obj.prePos = _obj.pos;
	_obj.preShadow = _obj.shadow;

	//���¾�����Ʈ
	_IState->UpdateState();

	//�߷��ۿ�
	gravity();

	//Ű�Է�
	keyInput();

	//�±�
	 hit();
	//���� ����
	if (_info.attackObj!=NULL)weaponUpdate();

	//������Ʈ ����
	_obj.update();
	_obj.shadowUpdate();
	
	//�ִ� ������ ����
	if (_info.rendType == RENDERTYPE::ANI_RENDER) _obj.ani->frameUpdate(TIME_M->getElapsedTime() * 7);

	//�����Ӿ���
	playFrame();

	if (KEY_M->isOnceKeyDown(VK_NUMPAD0))
	{
		cout << "�׸��� LT X: " << _obj.shadow.LT.x << endl;
		cout << "�׸��� LT Y: " << _obj.shadow.LT.y << endl;
		cout << "�׸��� LT Z: " << _obj.shadow.LT.z << endl;

		cout << "�׸��� pos X: " << _obj.shadow.pos.x << endl;
		cout << "�׸��� pos Y: " << _obj.shadow.pos.y << endl;
		cout << "�׸��� pos Z: " << _obj.shadow.pos.z << endl;

		cout << "ĳ���� X: " << _obj.pos.x << endl;
		cout << "ĳ���� Y: " << _obj.pos.y << endl;
		cout << "ĳ���� Z: " << _obj.pos.z << endl;
		if (_platform != nullptr)
		{
			cout << "�÷��� X: " << _platform->bottomPlane[0].getEnd().x << endl;
			cout << "�÷��� Y: " << _platform->bottomPlane[0].getEnd().y << endl;
			cout << "�÷��� Z: " << _platform->bottomPlane[0].getEnd().z << endl;
		}
		else cout << "NULL" << endl;
		
	}
	
}

//����
void Player::render()
{
	/*====================================================================
		Z-ORDER�� ���� ���� ������ ���� ��ŵ�ϴ�.
	====================================================================*/

	//�÷��̾� ������Ʈ ����
	ZORDER_M->renderObject(getMapDC(), &_obj, _info.rendType);

	//���⸦ ������ ���� ��(������������ �������� ���⸦ ����)
	if(!_info.hasWeapon)
	{ 
		//������Ʈ������ ���� �ʾҰ�, �������¶��
		if(_info.attackObj != NULL && _info.attackObj->isRender)
		ZORDER_M->renderObject(getMapDC(), _info.attackObj, RENDERTYPE::FRAME_RENDER);
	}

	//����� �� ��Ʈ ����
	if (KEY_M->isToggleKey(VK_SHIFT))
	{
		Rectangle(getMapDC(), _obj.shadow.rc);
		if(_info.isAttack) Rectangle(getMapDC(), _info.attackRc);
	}

	}

//���� ����
void Player::setState(PL_STATE state)
{
	if (_info.state == state)return;	//���� ���¸� �������� �ʴ´�.
	_info.preState = _info.state;		//���� �� ���� ���¸� �����Ѵ�.
	_info.state = state;				//���� ���¸� �����Ѵ�.

	//���¸� �������´�
	if (_IState != NULL) _IState->ExitState();

	//���¸� �����Ѵ�
	switch (_info.state)
	{
		//�⺻����
	case PL_STATE::IDLE:	    _IState = _idle;		 break;
	case PL_STATE::WAIT:	    _IState = _wait;		 break;
	case PL_STATE::WALK:	    _IState = _walk;		 break;
	case PL_STATE::RUN:		    _IState = _run;			 break;
	case PL_STATE::JUMP:		_IState = _jump;		 break;
	case PL_STATE::STICK:	    _IState = _stick;		 break;
	case PL_STATE::CLIMB:      _IState = _climb;		 break;
	case PL_STATE::CLIMBTOP:   _IState = _climbTop;		 break;
	case PL_STATE::PICK:      _IState = _pick;			 break;
		//���� �� �ǰ�
	case PL_STATE::GRAB:       _IState = _grab;			 break;
	case PL_STATE::GUARD:       _IState = _guard;		 break;
	case PL_STATE::ROLL:       _IState = _roll;			 break;
	case PL_STATE::HIT:		    _IState = _hit;			 break;
	case PL_STATE::STUN:        _IState = _stun;		 break;
	case PL_STATE::STAND:		_IState = _stand;		 break;
	case PL_STATE::DOWN:	    _IState = _down;		 break;
	case PL_STATE::DEAD:	    _IState = _dead;		 break;
		// ����
	case PL_STATE::THROW:	    _IState = _throw;		 break;
	case PL_STATE::STOMP:	    _IState = _stomp;		 break;
	case PL_STATE::COMBO1:	    _IState = _combo1;		 break;
	case PL_STATE::COMBO2:	    _IState = _combo2;		 break;
	case PL_STATE::COMBO3:	    _IState = _combo3;		 break;
	case PL_STATE::SATTACK:     _IState = _sAttack;		 break;
	case PL_STATE::DASHATTACK:  _IState = _dashAttack;	 break;
	case PL_STATE::DASHSATTACK: _IState = _dashSAttack;  break;
	case PL_STATE::JUMPATTACK:  _IState = _jumpAttack;	 break;
	case PL_STATE::SATTACKDOWN: _IState = _SAttackDown;  break;
	default: break;
	}

	//���¿� ��ũ�ϰ� �����Ѵ�.
	_IState->LinkPlAddress(this);
	_IState->EnterState();
}

//���� �� ����
bool Player::isRange(GameObject obj)
{
	//��ġ ���̰� 15�̸��̸�
	if (abs(_obj.pos.z - obj.pos.z) < 40) return true;
	return false;
}

//���� �� ����
bool Player::isRange(GameObject obj, float value)
{
	//��ġ ���̰� �� �̸��̸�
	if (abs(_obj.pos.z - obj.pos.z) < value) return true;
	return false;
}

//�������
void Player::weaponUpdate()
{
	if (!_info.attackObj) return;

	switch (_info.goalState)
	{
	case GOALPOS::PLAYER:
		break;
	case GOALPOS::WINOUT:
		//��� �̵��ϴٰ� ȭ��� ���� ����¸� �ٴ����� ����
		if (moveAttackObj())
		{
			if (_info.dest == DIRECTION::RIGHT) _info.attackGoal.x -= 30;
			if (_info.dest == DIRECTION::LEFT) _info.attackGoal.x += 30;
			_info.attackGoal.y = 0;
			_info.goalState = GOALPOS::FLOOR;
		}
		break;
	case GOALPOS::FLOOR:
		if (moveAttackObj())
		{
			_info.attackObj->isActive = true;
			_info.attackObj->isRender = true;
			_info.goalState = GOALPOS::PLAYER;
			_objectM->pushWeapon(WEAPON_TYPE::BAT, vector3(_info.attackGoal.x, _info.attackGoal.y, _info.attackGoal.z));
			_info.attackObj = NULL;
		}
		break;
	}
}

bool Player::moveAttackObj()
{
	_info.attackObj->pos.x += cosf(getAngle(_info.attackObj->pos.x, 0,  _info.attackGoal.x, 0)) * 6.0f;
	
	_info.attackObj->pos.z -= sinf(getAngle( 0 ,_info.attackObj->pos.z, 0 , _info.attackGoal.z)) * 6.0f;

	_info.attackObj->pos.y -= sinf(getAngle(0, _info.attackObj->pos.y, 0, _info.attackGoal.y)) * 6.0f;
	
	//���� ��Ʈ�� ���� ������Ʈ�� ��ġ�� ����.
	_info.attackRc = RectMakeCenter(_info.attackObj->pos.x,
		_info.attackObj->pos.z + _info.attackObj->pos.y,
		_info.attackObj->size.x + 200, _info.attackObj->size.z + 100);

	if (getDistance(_info.attackObj->pos.x, _info.attackObj->pos.z + _info.attackObj->pos.y,
		_info.attackGoal.x, _info.attackGoal.z + _info.attackGoal.y) < 5)
	{
		_info.attackObj->pos.x = _info.attackGoal.x;
		_info.attackObj->pos.y = _info.attackGoal.y;
		_info.attackObj->pos.z = _info.attackGoal.z;
		return true;
	}
	return false;
}

void Player::hit()
{
	//�̹�Ÿ�̸� ����
	if (!_info.isImmune)
	_info.immuneTimer = TIME_M->getWorldTime();

	//�̹û��¶�� 4���Ŀ� ���ư���
	 if (_info.isImmune && TIME_M->getWorldTime() - _info.immuneTimer > 4.f)
	{
		_info.isImmune = false;
		_obj.alpha = 255;
	}

	 //�÷��̾ �׾����� ����ó��
	 if (_info.hp <= 0)setState(PL_STATE::DEAD);

	//������ �ƴҶ� ������ �ƴҶ�
	if (_info.state != PL_STATE::DEAD && !_info.isImmune && _info.state != PL_STATE::STUN)
	{
		//������°� �ƴҶ� 
		if (_info.state != PL_STATE::GUARD)
		{
			for (int i = 0; i != _enemyM->getVEnemy().size(); i++)
			{
				if (_enemyM->getVEnemy()[i]->getInfo().isAttack)
				{
					RECT temp;
					if (IntersectRect(&temp, &_obj.rc, &_enemyM->getVEnemy()[i]->getInfo().rcAttack)
						&& isRange(_enemyM->getVEnemy()[i]->getRefObj()))
					{
						if (_info.hitCount >= 4)
						{ 
							//���� �� �ʱ�ȭ
							_info.hitCount = 0;
							if(_info.hp<=10)setState(PL_STATE::STUN);
							if (_info.hp > 10)setState(PL_STATE::DOWN); 
						}
						else setState(PL_STATE::HIT);
					}
				}
			}
			

		}

	}
}

//���������� �ٲ� ������ �ʱ�ȭ��Ű�� �Լ�
void Player::stageInit()
{
	/*====================================================================
		���������� �ٲ� ������ �ʱ�ȭ��Ű�� �Լ��Դϴ�.
	====================================================================*/
	switch (_stageM->getCurStage()) // ���� ����������?
	{
	case STAGETYPE::EASY: // ���� ���������� ������
		if (_stageM->getPreStage() == STAGETYPE::NORMAL) // ���� ���������� �븻�̿�����
		{
			_obj.setPosX(1445);
			_obj.setPosY(0);
			_obj.setPosZ(420);
		}
		break;
	case STAGETYPE::NORMAL:  // ���� ���������� �븻�̸�
		if (_stageM->getPreStage() == STAGETYPE::EASY) // ���� ���������� �븻�̿�����
		{
			_obj.setPosX(180);
			_obj.setPosY(0);
			_obj.setPosZ(700);
		}
		else if (_stageM->getPreStage() == STAGETYPE::HARD) // ���� ���������� �ϵ��̿�����
		{
			_obj.setPosX(2645);
			_obj.setPosY(0);
			_obj.setPosZ(670);
		}
		break;
	case STAGETYPE::HARD: // ���� ���������� �ϵ��
		if (_stageM->getPreStage() == STAGETYPE::NORMAL) // ���� ���������� �븻�̿�����
		{
			_obj.setPosX(270);
			_obj.setPosY(0); // ���߿� �߰��ؾ���
			_obj.setPosZ(480);
		}
		else if (_stageM->getPreStage() == STAGETYPE::BOSS) // ���� ���������� ����������
		{
			_obj.setPosX(2070);
			_obj.setPosY(0);
			_obj.setPosZ(1370);
		}
		break;
	case STAGETYPE::BOSS: // ���� ���������� ������
		if (_stageM->getPreStage() == STAGETYPE::HARD) // ���� ���������� �ϵ��̿�����
		{
			_obj.setPosX(275);
			_obj.setPosY(0);
			_obj.setPosZ(605);
		}
		break;
	default:
		break;
	}

	/*====================================================================
		��ũ : ���ʹ̸Ŵ���, ������Ʈ �Ŵ����� ��ũ�մϴ�.
	====================================================================*/
	_enemyM = _stageM->getStage()->getEnemyM();
	_objectM = _stageM->getStage()->getObjectM();
}

//�̹��� ����
void Player::changeImg(string imgName, bool reverse)
{
	//�̹����� �ٲ۴�.
	_obj.img = IMG_M->findImage(imgName);

	//����� ������ ���� ���� ������ x �ε��� ����
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		if (!reverse)_obj.imgIndex.x = 0;
		else if (reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX();
		_obj.imgIndex.y = 0;
		break;

	case DIRECTION::RIGHT:
		if (!reverse)_obj.imgIndex.x = _obj.img->getMaxFrameX();
		else if (reverse)_obj.imgIndex.x = 0;
		_obj.imgIndex.y = 1;
		break;
	}

	//������ �ð� �����Ͽ� �ٷ� ������ ����
	_info.frameTimer = TIME_M->getWorldTime();

}

//������ ����
void Player::setFrame(FRAMETYPE frameType, float frameInterval)
{
	//������ y ��ȣ ����
	switch (_info.dest)
	{
	case DIRECTION::LEFT:
		_obj.imgIndex.y = 0;
		break;
	case DIRECTION::RIGHT:
		_obj.imgIndex.y = 1;
		break;
	}
	if (_info.state == PL_STATE::CLIMB || _info.state == PL_STATE::CLIMBTOP)
		_obj.imgIndex.y = 0;
	//������ y ��ȣ ����
	_obj.img->setFrameY((int)_info.dest);

	//������ ���� �ð� ����
	if (TIME_M->getWorldTime() - _info.frameTimer > frameInterval)
	{
		//�ð� ����
		_info.frameTimer = TIME_M->getWorldTime();
		switch (_info.dest)
		{
		case DIRECTION::LEFT:
			if (frameType != FRAMETYPE::REVERSELOOP && frameType != FRAMETYPE::REVERSEONCE) ++_obj.imgIndex.x;
			else --_obj.imgIndex.x;


			break;
		case DIRECTION::RIGHT:
			if (frameType != FRAMETYPE::REVERSELOOP&& frameType != FRAMETYPE::REVERSEONCE) --_obj.imgIndex.x;
			else  ++_obj.imgIndex.x;
			break;
		}
	}

	//������ x ��ȣ ����
	switch (frameType)
	{
	case FRAMETYPE::ONCE://�� �� ���
	{
		//������ ��� x�ε����� 0������~ �������� �������� �� �Ǹ� ����ȣ�� �����ӹ�ȣ ����
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		}
		//�������� ��� x�ε����� �������� 0������ �������� �� �Ǹ� 0������ ������ ��ȣ ����
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0;
		}

	}
	break;
	case FRAMETYPE::LOOP://���� ���
	{
		//������ ��� x�ε����� 0������~ �������� �������� �� �Ǹ� ����ȣ�� �����ӹ�ȣ 0������ ����
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		//�������� ��� x�ε����� �������� 0������ �������� �� �Ǹ� 0������ ������ ��ȣ ����ȣ�� ����
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
	}
	break;
	case FRAMETYPE::REVERSEONCE://�ݴ� �ѹ� ���
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX(); return;
		}
		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0; return;
		}
	}
	break;
	case FRAMETYPE::REVERSELOOP://�ݴ� ���� ���
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();

	}
	break;
	}

}

//������ ����
void Player::playFrame()
{
	switch (_info.state)
	{
		//������� (�Ϲ� �ӵ�)
	case PL_STATE::WAIT:

		setFrame(FRAMETYPE::LOOP, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//�ݴ� ������� (����)
	case PL_STATE::RUN:
		setFrame(FRAMETYPE::REVERSELOOP, FRAMEINTERVAL*0.35);
		break;
		//�ݴ� �������
	case PL_STATE::STUN:
	case PL_STATE::IDLE:	case PL_STATE::WALK:
		setFrame(FRAMETYPE::REVERSELOOP, FRAMEINTERVAL);
		break;

		//�ѹ� (õõ��)
	case PL_STATE::PICK:	case PL_STATE::GRAB:
	case PL_STATE::STICK:	case PL_STATE::HIT:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL * 3);
	case PL_STATE::CLIMBTOP:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL * 5);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//�ѹ� (�Ϲ� �ӵ�)
	case PL_STATE::JUMP:
	case PL_STATE::ROLL:
	case PL_STATE::STAND:
	case PL_STATE::DOWN:	case PL_STATE::DEAD:
	case PL_STATE::THROW:
	case PL_STATE::COMBO1:	case PL_STATE::COMBO2:
	case PL_STATE::COMBO3:	case PL_STATE::SATTACK:
	case PL_STATE::DASHSATTACK:
	case PL_STATE::JUMPATTACK:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//�ݴ� �ѹ���� (�Ϲ� �ӵ�)
	case PL_STATE::STOMP:
	case PL_STATE::DASHATTACK:	case PL_STATE::SATTACKDOWN:
		setFrame(FRAMETYPE::REVERSEONCE, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//�ݴ� �ѹ���� (����)
	case PL_STATE::GUARD:
		setFrame(FRAMETYPE::REVERSEONCE, FRAMEINTERVAL*0.4);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//�ִϷ���
	case PL_STATE::CLIMB:
		_info.rendType = RENDERTYPE::ANI_RENDER;
		_obj.ani->setFPS(1);
		break;
	}

}

//��ǥ�̵�
void Player::movePos(float x, float z, float jumpPower)
{
	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//�׸��ڸ� �ϴ� �ѹ� ������Ʈ (�浹ó���� ���� ��! �ǵ帮�� �ȵ�!)
	_obj.shadowUpdate();

	//�浹ó�� 
	_colM->playerObjectCollision();

	//�׸��� �Ʒ��� �� ���������� ����ó��
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//���� ��Ʈ ����
	_obj.update();
}

//��ǥ����
void Player::setPos(float x, float z, float y)
{
	_obj.pos.x = x;
	_obj.pos.z = z;
	_obj.pos.y = y;

	//�׸��ڸ� �ϴ� �ѹ� ������Ʈ (�浹ó���� ���Ѱ�! �ǵ帮�� �ȵ�!)
	_obj.shadowUpdate();

	//�浹ó�� 
	_colM->playerObjectCollision();

	//�׸��� �Ʒ��� �� ���������� ����ó��
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//���� ��Ʈ ����
	_obj.update();
}


//�߷��ۿ�
void Player::gravity()
{
	if (_info.isSky) _info.jumpPower -= GRAVITY;
	if (_obj.pos.y >= 0 && _info.isSky)
	{
		setState(PL_STATE::IDLE);
		//�Ȱų� �ٰ��־���, Ű�� ��� ������������ �� ���� �״�ε��ƿ���
		if (_info.preState == PL_STATE::WALK || _info.preState == PL_STATE::RUN)
		{
			if (_info.dest == DIRECTION::LEFT && KEY_M->isStayKeyDown(VK_LEFT))setState(_info.preState);
			if (_info.dest == DIRECTION::RIGHT && KEY_M->isStayKeyDown(VK_RIGHT))setState(_info.preState);
		}
		_info.isSky = false;
		_platform = nullptr;
	}
	if (_obj.pos.y > 0) _info.jumpPower = 0;
	movePos(0, 0, _info.jumpPower);
}

//Ű�Է�
void Player::keyInput()
{
	//Ű������ ���ϴ� ���¶�� ����
	if (!_info.isControl) return;

	//����Ű�ޱ�(Ŀ�ǵ带����)
	if (KEY_M->isOnceKeyDownV('D'));

	//��ٸ�������
	if (_info.isClimb && (GetAsyncKeyState(VK_UP) & 0x8000)) setState(PL_STATE::CLIMB);

	//����
	if (KEY_M->isOnceKeyDownV('A') && !_info.isSky)
	{
		//�������� ����
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWER;
		movePos(0, 0, JUMPPOWER);
		//�����Ŀ��� - �� �������·� ��ȯ
		if (_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
	}
	//������
	if (KEY_M->isOnceKeyDownV('W') && !_info.isSky)
	{
		//�������� ����
		_info.preState = _info.state;
		setState(PL_STATE::ROLL);
	}

	//���������� ���ϴ� ���¶�� ����
	if (!_info.isConDest) return;

	//��
	if (KEY_M->isOnceKeyDownV(VK_LEFT) || KEY_M->isStayKeyDown(VK_LEFT))
	{
		_info.moveDest = MOVE_DIRECTION::LEFT;
		_info.dest = DIRECTION::LEFT;
	}
	//��
	if (KEY_M->isOnceKeyDownV(VK_RIGHT) || KEY_M->isStayKeyDown(VK_RIGHT))
	{
		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
	}
	//��
	if (KEY_M->isOnceKeyDownV(VK_UP) || KEY_M->isStayKeyDown(VK_UP))_info.moveDest = MOVE_DIRECTION::UP;
	//�Ʒ�
	if (KEY_M->isOnceKeyDownV(VK_DOWN) || KEY_M->isStayKeyDown(VK_DOWN))_info.moveDest = MOVE_DIRECTION::DOWN;


	//ŰĿ�ǵ� 
	if (!_info.isSky && KEY_M->getVKeyBuffer().size() >= 3)
	{
		//�ٶ󺸴� ����Ű+ �� + d Ŀ�ǵ� ����
		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_RIGHT && _info.dest == DIRECTION::RIGHT)
			setState(PL_STATE::SATTACKDOWN);

		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_LEFT && _info.dest == DIRECTION::LEFT)
			setState(PL_STATE::SATTACKDOWN);

	}
}
