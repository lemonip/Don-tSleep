#include "stdafx.h"
#include "playGround.h"

/*====================================================================
	playGround에서, 이미지를 추가하는 함수입니다.
	게임 내에서 쓰이는 모든 이미지는 이 곳에서 추가합니다.
====================================================================*/

void playGround::addImage()
{
	//================= 씬 이미지 =================
	IMG_M->addImage("load_background", "source/image/ui/scene/LoadingScene_Background.bmp", 1280, 720, true, MAGENTA);
	IMG_M->addFrameImage("loading_sprite", "source/image/ui/scene/loadingSprite.bmp", 1152, 227, 4, 1, false, MAGENTA);

	IMG_M->addImage("start_background", "source/image/ui/scene/StartScene_Background.bmp", 1600, 900, true, MAGENTA);
	IMG_M->addImage("start_title", "source/image/ui/scene/StartScene_Title.bmp", 537, 308, true, MAGENTA);
	IMG_M->addImage("start_kyoko", "source/image/ui/scene/StartScene_Kyoko.bmp", 550, 828, true, MAGENTA);

	//================= UI =================
	IMG_M->addImage("shadow", "source/image/character/shadow.bmp", 128, 38, true, MAGENTA, true);
	IMG_M->addImage("bossHPBack", "source/image/ui/battle/boss_HP_back.bmp", 898, 120, true, MAGENTA);
	IMG_M->addImage("bossHPFront", "source/image/ui/battle/boss_HP_front.bmp", 898, 120, true, MAGENTA);

	//================= 스테이지 =================
	IMG_M->addImage("easyStage", "source/image/stage/easy.bmp", 2704, 904, false, MAGENTA);
	IMG_M->addImage("normalStage", "source/image/stage/normal.bmp", 3820, 1116, false, MAGENTA);
	IMG_M->addImage("hardStage", "source/image/stage/hard.bmp", 3104, 1904, false, MAGENTA);
	IMG_M->addImage("bossStage", "source/image/stage/boss1.bmp", 2769, 1080, false, MAGENTA);
	IMG_M->addImage("bossStage2", "source/image/stage/boss2.bmp", 2769, 1080, false, MAGENTA);

	//================= 플래이어 =================

	IMG_M->addFrameImage("pl_climb", "source/image/character/player/climb.bmp", 720, 237, 6, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_climbTop", "source/image/character/player/climbTop.bmp", 288, 192, 3, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_comboAttack1", "source/image/character/player/comboAttack1.bmp", 1548, 462, 6, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_comboAttack2", "source/image/character/player/comboAttack2.bmp", 1869, 459, 7, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_comboAttack3", "source/image/character/player/comboAttack3.bmp", 2970, 462, 9, 2, true, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_dashAttack", "source/image/character/player/dashAttack.bmp", 2700, 436, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_dashSAttack", "source/image/character/player/dashSAttack.bmp", 5460, 456, 21, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_dead", "source/image/character/player/dead.bmp", 7280, 478, 26, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_down", "source/image/character/player/down.bmp", 4968, 390, 23, 2,true, MAGENTA, true);
	IMG_M->addFrameImage("pl_grab", "source/image/character/player/grab.bmp", 270, 384, 2, 2,true, MAGENTA, true);
	IMG_M->addFrameImage("pl_grabFail", "source/image/character/player/grabFail.bmp", 812, 422, 4, 2,true, MAGENTA, true);
	IMG_M->addFrameImage("pl_guard", "source/image/character/player/guard.bmp", 351, 464, 3, 2,true, MAGENTA, true);
	IMG_M->addFrameImage("pl_hit", "source/image/character/player/hit.bmp", 246, 456, 2, 2, true, MAGENTA, true);

	IMG_M->addFrameImage("pl_idle", "source/image/character/player/idle.bmp", 1440, 450, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_jump", "source/image/character/player/jump.bmp", 480, 640, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_jumpAttack", "source/image/character/player/jumpAttack.bmp", 1560, 432, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_pick", "source/image/character/player/pick.bmp", 222, 450, 2, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_roll", "source/image/character/player/roll.bmp", 900, 402, 9, 2, true, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_run", "source/image/character/player/run.bmp", 2736, 384, 16, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_sAttack", "source/image/character/player/sAttack.bmp", 3030, 560, 10, 2, true, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_sAttackDown", "source/image/character/player/sAttackDown.bmp", 7992, 438, 24, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_stand", "source/image/character/player/stand.bmp", 1863, 450, 9, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_stick", "source/image/character/player/stick.bmp", 294, 330, 2, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_stomp", "source/image/character/player/stomp.bmp", 1290, 420, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_stun", "source/image/character/player/stun.bmp", 384, 384, 4, 2, true, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_walk", "source/image/character/player/walk.bmp", 1476, 402, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wallet", "source/image/character/player/wallet.bmp", 2964, 420, 26, 2, true, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_wBatAttack", "source/image/character/player/wBatAttack.bmp", 1700, 700, 5, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatIdle", "source/image/character/player/wBatIdle.bmp", 1440, 560, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatJump", "source/image/character/player/wBatJump.bmp", 480, 640, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatRun", "source/image/character/player/wBatRun.bmp", 2736, 560, 16, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatThrow", "source/image/character/player/wBatThrow.bmp", 1616, 600, 8, 2, true, MAGENTA, true);

	//================= 에너미 =================
	IMG_M->addFrameImage("schoolGirl", "source/image/character/enemy/schoolGirl/idle.bmp", 1170, 354, 10,2,true, MAGENTA, true);
	//이미지등록은 schoolGirl ▲만 해놓고

	//▼이건 내가 없어서 예시로 이렇게 해야한다고 추가한것..ㅠㅠ
	IMG_M->addFrameImage("schoolGirlIdle", "source/image/character/enemy/schoolGirl/idle.bmp", 1170, 354, 10, 2, true, MAGENTA, true);

	//================= 오브젝트 =================
	IMG_M->addImage("desk", "source/image/object/desk.bmp", 98, 108, true, MAGENTA, true);

	//================= 아이템 =================
	IMG_M->addImage("meat", "source/image/item/meat.bmp", 60, 51, true, MAGENTA, true);
}