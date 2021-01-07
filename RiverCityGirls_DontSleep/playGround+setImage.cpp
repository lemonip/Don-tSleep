#include "stdafx.h"
#include "playGround.h"

/*====================================================================
	playGround에서, 이미지를 추가하는 함수입니다.
	게임 내에서 쓰이는 모든 이미지는 이 곳에서 추가합니다.
====================================================================*/

void playGround::addImage()
{
	//================= 씬 이미지 =================
	
	//로딩 씬
	IMG_M->addImage("load_background", "source/image/ui/scene/LoadingScene_Background.bmp", 1280, 720, true, MAGENTA);
	IMG_M->addFrameImage("loading_sprite", "source/image/ui/scene/loadingSprite.bmp", 1152, 227, 4, 1, false, MAGENTA);
	
	//시작 씬
	IMG_M->addImage("start_background", "source/image/ui/scene/StartScene_Background.bmp", 1280, 720, false, MAGENTA);
	IMG_M->addImage("start_frame", "source/image/ui/scene/StartScene_Frame.bmp", 1600, 900, true, MAGENTA);
	IMG_M->addImage("start_title", "source/image/ui/scene/StartScene_Title.bmp", 537, 308, true, MAGENTA);
	IMG_M->addImage("start_kyoko", "source/image/ui/scene/StartScene_Kyoko.bmp", 672, 1024, true, MAGENTA);
	IMG_M->addImage("start_misako", "source/image/ui/scene/StartScene_Misako.bmp", 672, 1024, true, MAGENTA);

	//선택 씬
	IMG_M->addImage("select_background", "source/image/ui/scene/SelectScene_Background.bmp", 1280, 720, false, MAGENTA);
	IMG_M->addImage("select_background2", "source/image/ui/scene/SelectScene_background2.bmp", 1280, 720, true, MAGENTA);
	IMG_M->addImage("select_illust", "source/image/ui/scene/SelectScene_illust.bmp", 996, 1705, true, MAGENTA);
	IMG_M->addImage("select_kyoko", "source/image/ui/scene/SelectScene_kyoko.bmp", 375, 675, true, MAGENTA);
	IMG_M->addImage("select_kyoko2", "source/image/ui/scene/SelectScene_kyoko2.bmp", 375, 675, true, MAGENTA);
	IMG_M->addImage("select_misako", "source/image/ui/scene/SelectScene_misako.bmp", 375, 675, true, MAGENTA);
	IMG_M->addImage("select_misako2", "source/image/ui/scene/SelectScene_misako2.bmp", 375, 675, true, MAGENTA);
	IMG_M->addImage("select_kyoko_background", "source/image/ui/scene/SelectScene_kyoko_background.bmp", 360, 563, true, MAGENTA);
	IMG_M->addImage("select_misako_background", "source/image/ui/scene/SelectScene_misako_background.bmp", 360, 563, true, MAGENTA);

	//================= UI =================
	IMG_M->addImage("shadow", "source/image/character/shadow.bmp", 128, 38, true, MAGENTA, true);
	IMG_M->addImage("bossHPBack", "source/image/ui/battle/boss_HP_back.bmp", 898, 120, true, MAGENTA);
	IMG_M->addImage("bossHPFront", "source/image/ui/battle/boss_HP_front.bmp", 898, 120, true, MAGENTA);
	IMG_M->addImage("save_load_close", "source/image/ui/scene/save_load_close.bmp", 365, 150, true, MAGENTA);
	IMG_M->addImage("save_load_open", "source/image/ui/scene/save_load_open.bmp", 365, 150, true, MAGENTA);

	//================= 스테이지 =================
	IMG_M->addImage("easyStage", "source/image/stage/easy.bmp", 2028, 678, false, MAGENTA);
	IMG_M->addImage("normalStage", "source/image/stage/normal.bmp", 2865, 837, false, MAGENTA);
	IMG_M->addImage("hardStage", "source/image/stage/hard.bmp", 2328, 1428, false, MAGENTA);
	IMG_M->addImage("bossStage", "source/image/stage/boss1.bmp", 2077, 810, false, MAGENTA);
	IMG_M->addImage("bossStage2", "source/image/stage/boss2.bmp", 2077, 810, false, MAGENTA);

	//================= 플래이어 =================
	IMG_M->addFrameImage("pl_climb", "source/image/character/player/climb.bmp", 720, 237, 6, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_climbTop", "source/image/character/player/climbTop.bmp", 288, 192, 3, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_comboAttack1", "source/image/character/player/comboAttack1.bmp", 1548, 390, 6, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_comboAttack2", "source/image/character/player/comboAttack2.bmp", 1869, 402, 7, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_comboAttack3", "source/image/character/player/comboAttack3.bmp", 2970, 462, 9, 2, true, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_dashAttack", "source/image/character/player/dashAttack.bmp", 2565, 414, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_dashSAttack", "source/image/character/player/dashSAttack.bmp", 5460, 456, 21, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_dead", "source/image/character/player/dead.bmp", 7280, 478, 26, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_down", "source/image/character/player/down.bmp", 4968, 390, 23, 2,true, MAGENTA, true);
	IMG_M->addFrameImage("pl_grab", "source/image/character/player/grab.bmp", 270, 384, 2, 2,true, MAGENTA, true);
	IMG_M->addFrameImage("pl_grabFail", "source/image/character/player/grabFail.bmp", 812, 422, 4, 2,true, MAGENTA, true);
	IMG_M->addFrameImage("pl_guard", "source/image/character/player/guard.bmp", 351, 378, 3, 2,true, MAGENTA, true);
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
	IMG_M->addFrameImage("pl_wait", "source/image/character/player/wait.bmp", 2520, 440, 18, 2, true, MAGENTA, true);
	
	IMG_M->addFrameImage("pl_wBatAttack", "source/image/character/player/wBatAttack.bmp", 1700, 700, 5, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatIdle", "source/image/character/player/wBatIdle.bmp", 1440, 560, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatJump", "source/image/character/player/wBatJump.bmp", 480, 640, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatRun", "source/image/character/player/wBatRun.bmp", 6784, 560, 16, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatThrow", "source/image/character/player/wBatThrow.bmp", 1616, 600, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_wBatWalk", "source/image/character/player/wBatWalk.bmp", 1476, 500, 12, 2, true, MAGENTA, true);

	//================= 에너미 =================
	IMG_M->addFrameImage("schoolGirl", "source/image/character/enemy/schoolGirl/idle.bmp", 1170, 354, 10,2,true, MAGENTA, true);
	//이미지등록은 schoolGirl ▲만 해놓고

	//▼이건 내가 없어서 예시로 이렇게 해야한다고 추가한것..ㅠㅠ
	IMG_M->addFrameImage("schoolGirlIdle", "source/image/character/enemy/schoolGirl/idle.bmp", 1170, 354, 10, 2, true, MAGENTA, true);
	//================= 보스 ====================
	IMG_M->addFrameImage("Bs_move", "source/image/character/enemy/boss/move.bmp", 2110, 588, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_idle", "source/image/character/enemy/boss/idle.bmp", 3180, 634, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_block", "source/image/character/enemy/boss/block.bmp", 1688, 576, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_attacked", "source/image/character/enemy/boss/attacked.bmp", 2214, 594, 9, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_groggy", "source/image/character/enemy/boss/groggy.bmp", 1024, 434, 4, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_phase", "source/image/character/enemy/boss/phase.bmp", 5658, 748, 23, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_down", "source/image/character/enemy/boss/down.bmp", 5830, 510, 22, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_death", "source/image/character/enemy/boss/death.bmp", 4576, 576, 13, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_howling", "source/image/character/enemy/boss/howling.bmp", 2916, 576, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_meteor", "source/image/character/enemy/boss/meteor_J.bmp", 1888, 672, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_dash", "source/image/character/enemy/boss/tackle_L.bmp", 2882, 576, 11, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_elbow", "source/image/character/enemy/boss/elbow.bmp", 2915, 652, 11, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_slap", "source/image/character/enemy/boss/slab.bmp", 5278, 582, 14, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_smash", "source/image/character/enemy/boss/smash.bmp", 11880, 594, 27, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_standat", "source/image/character/enemy/boss/standattack2.bmp", 3735, 580, 15, 2, true, MAGENTA, true);


	//================= 오브젝트 =================
	IMG_M->addImage("desk", "source/image/object/desk.bmp", 147, 162, true, MAGENTA, true);
	IMG_M->addImage("table", "source/image/object/table.bmp", 339, 162, true, MAGENTA, true);
	IMG_M->addFrameImage("vendingMachine", "source/image/object/vendingMachine.bmp", 525, 260, 2, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("bat", "source/image/object/bat.bmp", 179, 104, 1, 2, true, MAGENTA, true);
	//================= 아이템 =================
	IMG_M->addImage("meat", "source/image/item/meat.bmp", 60, 51, true, MAGENTA, true);
}