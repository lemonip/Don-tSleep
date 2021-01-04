#include "stdafx.h"
#include "playGround.h"

/*====================================================================
	playGround에서, 이미지를 추가하는 함수입니다.
	게임 내에서 쓰이는 모든 이미지는 이 곳에서 추가합니다.
====================================================================*/

void playGround::setImage()
{
	//================= 씬 이미지 =================
	IMG_M->addImage("start_background", "source/image/ui/scene/StartScene_Background.bmp", 1280, 720, true, MAGENTA);
	IMG_M->addImage("start_title", "source/image/ui/scene/StartScene_Title.bmp", 537, 308, true, MAGENTA);
	IMG_M->addImage("start_kyoko", "source/image/ui/scene/StartScene_Kyoko.bmp", 550, 828, true, MAGENTA);

	//================= UI =================
	IMG_M->addImage("shadow", "source/image/character/shadow.bmp", 128, 38, true, MAGENTA, true);


	//================= 스테이지 =================
	IMG_M->addImage("easyStage", "source/image/stage/easy.bmp", 2704, 904, false, MAGENTA);
	IMG_M->addImage("normalStage", "source/image/stage/normal.bmp", 3820, 1116, false, MAGENTA);
	IMG_M->addImage("hardStage", "source/image/stage/hard.bmp", 3104, 1904, false, MAGENTA);
	IMG_M->addImage("bossStage", "source/image/stage/boss1.bmp", 2769, 1080, false, MAGENTA);
	IMG_M->addImage("bossStage2", "source/image/stage/boss2.bmp", 2769, 1080, false, MAGENTA);

	//================= 플래이어 =================
	IMG_M->addFrameImage("pl_comboAttack3", "source/image/character/player/comboAttack3.bmp", 2970, 462, 9, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_comboAttack2", "source/image/character/player/comboAttack2.bmp", 1869, 459, 7, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_comboAttack1", "source/image/character/player/comboAttack1.bmp", 1548, 462, 6, 2, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_dashAttack", "source/image/character/player/dashAttack.bmp", 2700, 436, 8, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_dashSAttack", "source/image/character/player/dashSAttack.bmp", 5040, 456, 21, 2, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_dead", "source/image/character/player/dead.bmp", 6240, 477, 26, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_down", "source/image/character/player/down.bmp", 4896, 452, 24, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_guard", "source/image/character/player/guard.bmp", 351, 464, 3, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_hit", "source/image/character/player/hit.bmp", 246, 456, 2, 2, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_idle", "source/image/character/player/idle.bmp", 1440, 450, 12, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_jump", "source/image/character/player/jump.bmp", 405, 414, 3, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_jumpAttack", "source/image/character/player/jumpAttack.bmp", 1560, 432, 10, 2, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_run", "source/image/character/player/run.bmp", 2736, 384, 16, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_sAttack", "source/image/character/player/sAttack.bmp", 3030, 560, 10, 2, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_sAttackDown", "source/image/character/player/sAttackDown.bmp", 2994, 657, 9, 3, MAGENTA, true);
	IMG_M->addFrameImage("pl_stun", "source/image/character/player/stun.bmp", 384, 384, 4, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_stand", "source/image/character/player/stand.bmp", 3315, 457, 15, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_stomp", "source/image/character/player/stomp.bmp", 1290, 451, 4, 2, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_walk", "source/image/character/player/walk.bmp", 1476, 402, 12, 2, MAGENTA, true);
	IMG_M->addFrameImage("pl_wallet", "source/image/character/player/wallet.bmp", 2964, 420, 26, 2, MAGENTA, true);

	//================= 에너미 =================
	IMG_M->addFrameImage("schoolGirl", "source/image/character/enemy/schoolGirl/idle.bmp", 1170, 354, 10,2,true, MAGENTA, true);

	//================= 오브젝트 =================
	IMG_M->addImage("desk", "source/image/object/desk.bmp", 98, 108, true, MAGENTA, true);

	//================= 아이템 =================
	IMG_M->addImage("meat", "source/image/item/meat.bmp", 60, 51, true, MAGENTA, true);
}