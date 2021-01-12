#include "stdafx.h"
#include "Player.h"
//?¸ë?
#include "StageManager.h"
#include "Stage.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "CollisionManager.h"
#include "Enemy.h"
#include "ItemObj.h"
#include "Object.h"
//»óÅÂ
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
//ì´ˆê¸°??
HRESULT Player::init()
{
	/*====================================================================
		?Œë˜?´ì–´???¤ë¸Œ?íŠ¸ ì´ˆê¸°?”ì? ê¸°ë³¸ ?¤ì •???©ë‹ˆ??
	====================================================================*/
	_obj.init(OBJECT_GROUP::PLAYER, IMG_M->findImage("pl_wait"), vector3(WINSIZEX / 2, 0, WINSIZEY / 2 + 200));

	//ê¸°ë³¸ ë³€??ì´ˆê¸°??
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

	//?íƒœ?¨í„´ ?±ë¡
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

//?…ëƒ ?œì„œ ì¤‘ìš”?¨â˜… ?íƒœ->ì¤‘ë ¥->?¤ì…??
void Player::update()
{
	//cout << (int)_info.state<< endl;

	_obj.prePos = _obj.pos;
	_obj.preShadow = _obj.shadow;

	//?íƒœ?…ë°?´íŠ¸
	_IState->UpdateState();

	//ì¤‘ë ¥?‘ìš©
	gravity();

	//?¤ì…??
	keyInput();

	
	 hit();
	 //ë¬´ê¸° ?…ëƒ
	if (_info.attackObj!=NULL)weaponUpdate();
	//¾ÆÀÌÅÛ »óÈ£ÀÛ¿ë
	checkItem();

	//?¤ë¸Œ?íŠ¸ ?…ëƒ
	_obj.update();
	_obj.shadowUpdate();
	
	//? ë‹ˆ ?„ë ˆ???…ëƒ
	if (_info.rendType == RENDERTYPE::ANI_RENDER) _obj.ani->frameUpdate(TIME_M->getElapsedTime() * 7);

	//?„ë ˆ?„ì—…??
	playFrame();

	if (KEY_M->isOnceKeyDown(VK_NUMPAD0))
	{
		cout << "ê·¸ë¦¼??LT X: " << _obj.shadow.LT.x << endl;
		cout << "ê·¸ë¦¼??LT Y: " << _obj.shadow.LT.y << endl;
		cout << "ê·¸ë¦¼??LT Z: " << _obj.shadow.LT.z << endl;

		cout << "ê·¸ë¦¼??pos X: " << _obj.shadow.pos.x << endl;
		cout << "ê·¸ë¦¼??pos Y: " << _obj.shadow.pos.y << endl;
		cout << "ê·¸ë¦¼??pos Z: " << _obj.shadow.pos.z << endl;

		cout << "ìºë¦­??X: " << _obj.pos.x << endl;
		cout << "ìºë¦­??Y: " << _obj.pos.y << endl;
		cout << "ìºë¦­??Z: " << _obj.pos.z << endl;
		if (_platform != nullptr)
		{
			cout << "?Œë«??X: " << _platform->bottomPlane[0].getEnd().x << endl;
			cout << "?Œë«??Y: " << _platform->bottomPlane[0].getEnd().y << endl;
			cout << "?Œë«??Z: " << _platform->bottomPlane[0].getEnd().z << endl;
		}
		else cout << "NULL" << endl;
		
	}
	
}

//?Œë”
void Player::render()
{
	/*====================================================================
		Z-ORDER???°ë¼ ?ŒíŒŒ ?„ë ˆ???Œë” ?œí‚µ?ˆë‹¤.
	====================================================================*/

	//?Œë˜?´ì–´ ?¤ë¸Œ?íŠ¸ ?Œë”
	ZORDER_M->renderObject(getMapDC(), &_obj, _info.rendType);

	//ë¬´ê¸°ë¥?ê°€ì§€ê³??ˆì„ ???˜ì ¸ë²„ë ¸?„ë•Œ ?˜ì ¸ì§€??ë¬´ê¸°ë¥??Œë”)
	if(!_info.hasWeapon)
	{ 
		//?¤ë¸Œ?íŠ¸ì°¸ì¡°ë¥??ƒì? ?Šì•˜ê³? ?Œë”?íƒœ?¼ë©´
		if(_info.attackObj != NULL && _info.attackObj->isRender)
		ZORDER_M->renderObject(getMapDC(), _info.attackObj, RENDERTYPE::FRAME_RENDER);
	}

	//?”ë²„ê¹????‰íŠ¸ ?Œë”
	if (KEY_M->isToggleKey(VK_SHIFT))
	{
		Rectangle(getMapDC(), _obj.shadow.rc);
		if(_info.isAttack) Rectangle(getMapDC(), _info.attackRc);
	}

	}

//?íƒœ ì§€??
void Player::setState(PL_STATE state)
{
	if (_info.state == state)return;	//ê°™ì? ?íƒœë©?ë³€ê²½í•˜ì§€ ?ŠëŠ”??
	_info.preState = _info.state;		//ë³€ê²????„ì¬ ?íƒœë¥??€?¥í•œ??
	_info.state = state;				//?„ì¬ ?íƒœë¥?ë³€ê²½í•œ??

	//?íƒœë¥?ë¹ ì ¸?˜ì˜¨??
	if (_IState != NULL) _IState->ExitState();

	//?íƒœë¥?ë³€ê²½í•œ??
	switch (_info.state)
	{
		//ê¸°ë³¸?™ì‘
	case PL_STATE::IDLE:	    _IState = _idle;		 break;
	case PL_STATE::WAIT:	    _IState = _wait;		 break;
	case PL_STATE::WALK:	    _IState = _walk;		 break;
	case PL_STATE::RUN:		    _IState = _run;			 break;
	case PL_STATE::JUMP:		_IState = _jump;		 break;
	case PL_STATE::STICK:	    _IState = _stick;		 break;
	case PL_STATE::CLIMB:      _IState = _climb;		 break;
	case PL_STATE::CLIMBTOP:   _IState = _climbTop;		 break;
	case PL_STATE::PICK:      _IState = _pick;			 break;
		//ê°€??ë°??¼ê²©
	case PL_STATE::GRAB:       _IState = _grab;			 break;
	case PL_STATE::GUARD:       _IState = _guard;		 break;
	case PL_STATE::ROLL:       _IState = _roll;			 break;
	case PL_STATE::HIT:		    _IState = _hit;			 break;
	case PL_STATE::STUN:        _IState = _stun;		 break;
	case PL_STATE::STAND:		_IState = _stand;		 break;
	case PL_STATE::DOWN:	    _IState = _down;		 break;
	case PL_STATE::DEAD:	    _IState = _dead;		 break;
		// ê³µê²©
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

	//?íƒœ??ë§í¬?˜ê³  ì§„ì…?œë‹¤.
	_IState->LinkPlAddress(this);
	_IState->EnterState();
}

//ê°™ì? ì¤?? ë¬´
bool Player::isRange(GameObject obj)
{
	//?„ì¹˜ ì°¨ì´ê°€ 15ë¯¸ë§Œ?´ë©´
	if (abs(_obj.pos.z - obj.pos.z) < 40) return true;
	return false;
}

//ê°™ì? ì¤?? ë¬´
bool Player::isRange(GameObject obj, float value)
{
	//?„ì¹˜ ì°¨ì´ê°€ ê°?ë¯¸ë§Œ?´ë©´
	if (abs(_obj.pos.z - obj.pos.z) < value) return true;
	return false;
}

//ë¬´ê¸°?…ëƒ
void Player::weaponUpdate()
{
	if (!_info.attackObj) return;

	switch (_info.goalState)
	{
	case GOALPOS::PLAYER:
		break;
	case GOALPOS::WINOUT:
		//ê³¨ë¡œ ?´ë™?˜ë‹¤ê°€ ?”ë©´ê³¨ì— ê°€ë©?ê³¨ìƒ?œë? ë°”ë‹¥?¼ë¡œ ë³€ê²?
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
	
	//ê³µê²© ?‰íŠ¸ ?ì„±
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
	//?´ë? ?íƒœê°€ ?„ë‹ˆë©??€?´ë¨¸ ì´ˆê¸°??
	if (!_info.isImmune)
	_info.immuneTimer = TIME_M->getWorldTime();

	//?´ë? ?íƒœê³?4ì´ˆê? ì§€?¬ë‹¤ë©??´ë? ?ë‚¨
	 if (_info.isImmune && TIME_M->getWorldTime() - _info.immuneTimer > 4.f)
	{
		_info.isImmune = false;
		_obj.alpha = 255;
	}

	 //?¼ê? 0?´í•˜ê°€ ?˜ë©´
	 if (_info.hp <= 0)setState(PL_STATE::DEAD);

	//Dead ?íƒœê°€ ?„ë‹ˆê³??´ë????„ë‹ˆê³??¤í„´ ?íƒœê°€ ?„ë‹ˆë©?
	if (_info.state != PL_STATE::DEAD && !_info.isImmune && _info.state != PL_STATE::STUN)
	{
		//ê°€???íƒœê°€ ?„ë‹ˆë©?
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
							//?¼ê? 10 ?´í•˜ë©??¤í„´ / 10 ì´ˆê³¼ë©??¤ìš´ ?íƒœ
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


//?¤í…Œ?´ì?ê°€ ë°”ë€??Œë§ˆ??ì´ˆê¸°?”ì‹œ?¤ëŠ” ?¨ìˆ˜
void Player::stageInit()
{
	/*====================================================================
		?¤í…Œ?´ì?ê°€ ë°”ë€??Œë§ˆ??ì´ˆê¸°?”ì‹œ?¤ëŠ” ?¨ìˆ˜?…ë‹ˆ??
	====================================================================*/
	switch (_stageM->getCurStage()) // ?„ì¬ ?¤í…Œ?´ì???
	{
	case STAGETYPE::EASY: // ?„ì¬ ?¤í…Œ?´ì?ê°€ ?´ì?ë©?
		if (_stageM->getPreStage() == STAGETYPE::NORMAL) // ?´ì „ ?¤í…Œ?´ì?ê°€ ?¸ë§?´ì??¼ë©´
		{
			_obj.setPosX(1445);
			_obj.setPosY(0);
			_obj.setPosZ(420);
		}
		break;
	case STAGETYPE::NORMAL:  // ?„ì¬ ?¤í…Œ?´ì?ê°€ ?¸ë§?´ë©´
		if (_stageM->getPreStage() == STAGETYPE::EASY) // ?´ì „ ?¤í…Œ?´ì?ê°€ ?¸ë§?´ì??¼ë©´
		{
			_obj.setPosX(180);
			_obj.setPosY(0);
			_obj.setPosZ(700);
		}
		else if (_stageM->getPreStage() == STAGETYPE::HARD) // ?´ì „ ?¤í…Œ?´ì?ê°€ ?˜ë“œ?´ì??¼ë©´
		{
			_obj.setPosX(2645);
			_obj.setPosY(0);
			_obj.setPosZ(670);
		}
		break;
	case STAGETYPE::HARD: // ?„ì¬ ?¤í…Œ?´ì?ê°€ ?˜ë“œë©?
		if (_stageM->getPreStage() == STAGETYPE::NORMAL) // ?´ì „ ?¤í…Œ?´ì?ê°€ ?¸ë§?´ì??¼ë©´
		{
			_obj.setPosX(270);
			_obj.setPosY(0); 
			_obj.setPosZ(480);
		}
		else if (_stageM->getPreStage() == STAGETYPE::BOSS) // ?´ì „ ?¤í…Œ?´ì?ê°€ ë³´ìŠ¤?€?¼ë©´
		{
			_obj.setPosX(2070);
			_obj.setPosY(0);
			_obj.setPosZ(1370);
		}
		break;
	case STAGETYPE::BOSS: // ?„ì¬ ?¤í…Œ?´ì?ê°€ ë³´ìŠ¤ë©?
		if (_stageM->getPreStage() == STAGETYPE::HARD) // ?´ì „ ?¤í…Œ?´ì?ê°€ ?˜ë“œ?´ì??¼ë©´
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
		ë§í¬ : ?ë„ˆë¯¸ë§¤?ˆì?, ?¤ë¸Œ?íŠ¸ ë§¤ë‹ˆ?€?€ ë§í¬?©ë‹ˆ??
	====================================================================*/
	_enemyM = _stageM->getStage()->getEnemyM();
	_objectM = _stageM->getStage()->getObjectM();
}

//?´ë?ì§€ ë³€ê²?
void Player::changeImg(string imgName, bool reverse)
{
	//?´ë?ì§€ë¥?ë°”ê¾¼??
	_obj.img = IMG_M->findImage(imgName);

	//ë°©í–¥ê³?ë¦¬ë²„???¬ë? ?°ë¥¸ ?„ë ˆ??x ?¸ë±???¤ì •
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

	//?„ë ˆ???œê°„ ê°±ì‹ ?˜ì—¬ ë°”ë¡œ ?„ë ˆ??ë³€ê²?
	_info.frameTimer = TIME_M->getWorldTime();

}

//?„ë ˆ???°ì‚°
void Player::setFrame(FRAMETYPE frameType, float frameInterval)
{
	//?„ë ˆ??y ë²ˆí˜¸ ?¤ì •
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
	//?„ë ˆ??y ë²ˆí˜¸ ?¸íŒ…
	_obj.img->setFrameY((int)_info.dest);

	//?„ë ˆ???¤í–‰ ?œê°„ ?¤ì •
	if (TIME_M->getWorldTime() - _info.frameTimer > frameInterval)
	{
		//?œê°„ ê°±ì‹ 
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

	//?„ë ˆ??x ë²ˆí˜¸ ì¡°ì ˆ
	switch (frameType)
	{
	case FRAMETYPE::ONCE://??ë²??¬ìƒ
	{
		//?¼ìª½??ê²½ìš° x?¸ë±?¤ê? 0ë²ˆë??? ?ë²ˆê¹Œì? ?„ë ˆ?„ì´ ???˜ë©´ ?ë²ˆ?¸ë¡œ ?„ë ˆ?„ë²ˆ??ê³ ì •
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
		{
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
		}
		//?¤ë¥¸ìª½ì˜ ê²½ìš° x?¸ë±?¤ê? ?ë²ˆë¶€??0ë²ˆê¹Œì§€ ?„ë ˆ?„ì´ ???˜ë©´ 0ë²ˆìœ¼ë¡??„ë ˆ??ë²ˆí˜¸ ê³ ì •
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
		{
			_obj.imgIndex.x = 0;
		}

	}
	break;
	case FRAMETYPE::LOOP://ë¬´í•œ ?¬ìƒ
	{
		//?¼ìª½??ê²½ìš° x?¸ë±?¤ê? 0ë²ˆë??? ?ë²ˆê¹Œì? ?„ë ˆ?„ì´ ???˜ë©´ ?ë²ˆ?¸ë¡œ ?„ë ˆ?„ë²ˆ??0ë²ˆìœ¼ë¡?ê°±ì‹ 
		if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		//?¤ë¥¸ìª½ì˜ ê²½ìš° x?¸ë±?¤ê? ?ë²ˆë¶€??0ë²ˆê¹Œì§€ ?„ë ˆ?„ì´ ???˜ë©´ 0ë²ˆìœ¼ë¡??„ë ˆ??ë²ˆí˜¸ ?ë²ˆ?¸ë¡œ ê°±ì‹ 
		else if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();
	}
	break;
	case FRAMETYPE::REVERSEONCE://ë°˜ë? ?œë²ˆ ?¬ìƒ
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
	case FRAMETYPE::REVERSELOOP://ë°˜ë? ë¬´í•œ ?¬ìƒ
	{
		if (_info.dest == DIRECTION::RIGHT && _obj.imgIndex.x > _obj.img->getMaxFrameX())
			_obj.imgIndex.x = 0;

		else if (_info.dest == DIRECTION::LEFT && _obj.imgIndex.x < 0)
			_obj.imgIndex.x = _obj.img->getMaxFrameX();

	}
	break;
	}

}

//?„ë ˆ???¤í–‰
void Player::playFrame()
{
	switch (_info.state)
	{
		//ë¬´í•œ?¬ìƒ (?¼ë°˜ ?ë„)
	case PL_STATE::WAIT:

		setFrame(FRAMETYPE::LOOP, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//ë°˜ë? ë¬´í•œ?¬ìƒ (ë¹¨ë¦¬)
	case PL_STATE::RUN:
		setFrame(FRAMETYPE::REVERSELOOP, FRAMEINTERVAL*0.35);
		break;
		//ë°˜ë? ë¬´í•œ?¬ìƒ
	case PL_STATE::STUN:
	case PL_STATE::IDLE:	case PL_STATE::WALK:
		setFrame(FRAMETYPE::REVERSELOOP, FRAMEINTERVAL);
		break;

		//?œë²ˆ (ì²œì²œ??
	case PL_STATE::PICK:	case PL_STATE::GRAB:
	case PL_STATE::STICK:	case PL_STATE::HIT:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL * 3);
	case PL_STATE::CLIMBTOP:
		setFrame(FRAMETYPE::ONCE, FRAMEINTERVAL * 5);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//?œë²ˆ (?¼ë°˜ ?ë„)
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
		//ë°˜ë? ?œë²ˆ?¬ìƒ (?¼ë°˜ ?ë„)
	case PL_STATE::STOMP:
	case PL_STATE::DASHATTACK:	case PL_STATE::SATTACKDOWN:
		setFrame(FRAMETYPE::REVERSEONCE, FRAMEINTERVAL);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//ë°˜ë? ?œë²ˆ?¬ìƒ (ë¹¨ë¦¬)
	case PL_STATE::GUARD:
		setFrame(FRAMETYPE::REVERSEONCE, FRAMEINTERVAL*0.4);
		_info.rendType = RENDERTYPE::FRAME_RENDER;
		break;
		//? ë‹ˆ?œë”
	case PL_STATE::CLIMB:
		_info.rendType = RENDERTYPE::ANI_RENDER;
		_obj.ani->setFPS(1);
		break;
	}

}

//ì¢Œí‘œ?´ë™
void Player::movePos(float x, float z, float jumpPower)
{
	_obj.pos.x += x;
	_obj.pos.z += z;
	_obj.pos.y -= jumpPower;

	//ê·¸ë¦¼?ë§Œ ?¼ë‹¨ ?œë²ˆ ?…ë°?´íŠ¸ (ì¶©ëŒì²˜ë¦¬ë¥??„í•œ ê±? ê±´ë“œë¦¬ë©´ ?ˆë¨!)
	_obj.shadowUpdate();

	//ì¶©ëŒì²˜ë¦¬
	_colM->playerObjectCollision();

	//ê·¸ë¦¼???„ë˜ë¡????¨ì–´ì§€?„ë¡ ?ˆì™¸ì²˜ë¦¬
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//ìµœì¢… ?‰íŠ¸ ê°±ì‹ 
	_obj.update();
}

//ì¢Œí‘œ?¤ì •
void Player::setPos(float x, float z, float y)
{
	_obj.pos.x = x;
	_obj.pos.z = z;
	_obj.pos.y = y;

	//ê·¸ë¦¼?ë§Œ ?¼ë‹¨ ?œë²ˆ ?…ë°?´íŠ¸ (ì¶©ëŒì²˜ë¦¬ë¥??„í•œê±? ê±´ë“œë¦¬ë©´ ?ˆë¨!)
	_obj.shadowUpdate();

	//ì¶©ëŒì²˜ë¦¬
	_colM->playerObjectCollision();

	//ê·¸ë¦¼???„ë˜ë¡????¨ì–´ì§€?„ë¡ ?ˆì™¸ì²˜ë¦¬
	if (_obj.pos.y > 0)_obj.pos.y = 0;

	//ìµœì¢… ?‰íŠ¸ ê°±ì‹ 
	_obj.update();
}

//¾ÆÀÌÅÛÀÌ¶û »óÈ£ÀÛ¿ë
void Player::checkItem()
{
	RECT temp;
	for (int i = 0; i != _objectM->getVObject().size();i++)
	{
		//È°¼ºÈ­ »óÅÂÀÏ¶§
		if (_objectM->getVObject()[i]->getObj()->isActive)
		{
			// Ãæµ¹ÇÑ´Ù¸é
			if (IntersectRect(&temp, &_obj.rc, &_objectM->getVObject()[i]->getRefObj().rc))
			{
				switch (_objectM->getVObject()[i]->getInfo().type)
				{
				//¼ÒÁö±İ ¿Ã·ÁÁÜ
				case ITEM_TYPE::MONEY:
					break;
				case ITEM_TYPE::COIN:
					break;
				//Ã¼·ÂÈ¸º¹
				case ITEM_TYPE::MEAT:
				case ITEM_TYPE::APPLE:
				case ITEM_TYPE::HEN:
				case ITEM_TYPE::CHILI:
					if (_info.hp < _info.maxHP)
					{
						_info.hp += _objectM->getVObject()[i]->getInfo().healValue;
						_objectM->popObject(i);
						if (i == _objectM->getVObject().size())return;
					}
					break;
				}
			}
			
		}
	}

	//Ã¼·Â¼öÄ¡ º¸Á¤
	if (_info.hp > _info.maxHP)
	{
		_info.hp = _info.maxHP;
	}
}


//ì¤‘ë ¥?‘ìš©
void Player::gravity()
{
	if (_info.isSky) _info.jumpPower -= GRAVITY;
	if (_obj.pos.y >= 0 && _info.isSky)
	{
		setState(PL_STATE::IDLE);
		//ê±·ê±°???°ê³ ?ˆì—ˆê³? ?¤ë? ê³„ì† ?„ë¥´ê³ ìˆ?¼ë©´ ê·??íƒœ ê·¸ë?ë¡œëŒ?„ì˜¤ê¸?
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

//?¤ì…??
void Player::keyInput()
{
	//?¤ì¡°?‘ì„ ëª»í•˜???íƒœ?¼ë©´ ë¦¬í„´
	if (!_info.isControl) return;

	//ê³µê²©?¤ë°›ê¸?ì»¤ë§¨?œë??„í•´)
	if (KEY_M->isOnceKeyDownV('D'));

	//?¬ë‹¤ë¦¬ì˜¤ë¥´ê¸°
	if (_info.isClimb && (GetAsyncKeyState(VK_UP) & 0x8000)) setState(PL_STATE::CLIMB);

	//?í”„
	if (KEY_M->isOnceKeyDownV('A') && !_info.isSky)
	{
		//?´ì „?íƒœ ?€??
		_info.preState = _info.state;
		_info.isSky = true;
		_info.jumpPower = JUMPPOWER;
		movePos(0, 0, JUMPPOWER);
		//?í”„?Œì›Œê°€ - ë©??í”„?íƒœë¡??„í™˜
		if (_info.jumpPower > 0.4)setState(PL_STATE::JUMP);
	}
	//êµ¬ë¥´ê¸?
	if (KEY_M->isOnceKeyDownV('W') && !_info.isSky)
	{
		//?´ì „?íƒœ ?€??
		_info.preState = _info.state;
		setState(PL_STATE::ROLL);
	}

	//ë°©í–¥ì¡°ì‘??ëª»í•˜???íƒœ?¼ë©´ ë¦¬í„´
	if (!_info.isConDest) return;

	//??
	if (KEY_M->isOnceKeyDownV(VK_LEFT) || KEY_M->isStayKeyDown(VK_LEFT))
	{
		_info.moveDest = MOVE_DIRECTION::LEFT;
		_info.dest = DIRECTION::LEFT;
	}
	//??
	if (KEY_M->isOnceKeyDownV(VK_RIGHT) || KEY_M->isStayKeyDown(VK_RIGHT))
	{
		_info.moveDest = MOVE_DIRECTION::RIGHT;
		_info.dest = DIRECTION::RIGHT;
	}
	//??
	if (KEY_M->isOnceKeyDownV(VK_UP) || KEY_M->isStayKeyDown(VK_UP))_info.moveDest = MOVE_DIRECTION::UP;
	//?„ë˜
	if (KEY_M->isOnceKeyDownV(VK_DOWN) || KEY_M->isStayKeyDown(VK_DOWN))_info.moveDest = MOVE_DIRECTION::DOWN;


	//?¤ì»¤ë§¨ë“œ
	if (!_info.isSky && KEY_M->getVKeyBuffer().size() >= 3)
	{
		//ë°”ë¼ë³´ëŠ” ë°©í–¥?? ??+ d ì»¤ë§¨??ê³µê²©
		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_RIGHT && _info.dest == DIRECTION::RIGHT)
			setState(PL_STATE::SATTACKDOWN);

		if (KEY_M->getKeyBuffer(0) == 'D' &&KEY_M->getKeyBuffer(1) == VK_DOWN
			&& KEY_M->getKeyBuffer(2) == VK_LEFT && _info.dest == DIRECTION::LEFT)
			setState(PL_STATE::SATTACKDOWN);

	}
}
