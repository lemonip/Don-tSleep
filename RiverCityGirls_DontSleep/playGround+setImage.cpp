#include "stdafx.h"
#include "playGround.h"


/*====================================================================
	playGround에서, 이미지를 추가하는 함수입니다.
	게임 내에서 쓰이는 모든 이미지는 이 곳에서 추가합니다.
====================================================================*/

void playGround::addSource()
{
	//================= 스테이지 =================
	SOUND_M->addSound("bossStage", "source/bgm/bossStage.mp3", tagVolumeType::MUSIC, true);
	SOUND_M->addSound("hardStage", "source/bgm/hardStage.mp3", tagVolumeType::MUSIC, true);
	SOUND_M->addSound("menuBG", "source/bgm/menuBG.mp3", tagVolumeType::MUSIC, true);
	SOUND_M->addSound("openingBG", "source/bgm/openingBG.mp3", tagVolumeType::MUSIC, true);
	SOUND_M->addSound("shopBG", "source/bgm/shopBG.mp3", tagVolumeType::MUSIC, true);
	SOUND_M->addSound("stage", "source/bgm/stage.mp3", tagVolumeType::MUSIC, true);

	//================= 플레이어 =================
	SOUND_M->addSound("kyoko_battlestart", "source/mr/playerMr/kyoko_battlestart.mp3", tagVolumeType::SFX, false);
	SOUND_M->addSound("kyoko_coin", "source/mr/playerMr/kyoko_coin.mp3", tagVolumeType::SFX, false);
	SOUND_M->addSound("kyoko_combo", "source/mr/playerMr/kyoko_combo.mp3", tagVolumeType::SFX, false);
	SOUND_M->addSound("kyoko_dashSAttack", "source/mr/playerMr/kyoko_dashSAttack.mp3", tagVolumeType::SFX, false);
	SOUND_M->addSound("kyoko_hurricane", "source/mr/playerMr/kyoko_hurricane.mp3", tagVolumeType::SFX, false);
	SOUND_M->addSound("kyoko_jumpAttack", "source/mr/playerMr/kyoko_jumpAttack.mp3", tagVolumeType::SFX, false);
	SOUND_M->addSound("kyoko_sAttack", "source/mr/playerMr/kyoko_sAttack.mp3", tagVolumeType::SFX, false);
	SOUND_M->addSound("kyoko_weapon_bat", "source/mr/playerMr/kyoko_weapon_bat.mp3", tagVolumeType::SFX, false);

}


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
	
	//상점 씬
	IMG_M->addImage("shop_background", "source/image/ui/scene/ShopScene_background.bmp", 1280, 720, false, MAGENTA);


	//게임 씬
	IMG_M->addImage("dialogWindow", "source/image/ui/scene/dialogWindow.bmp", 1280, 150, true, MAGENTA);
	IMG_M->addImage("kyoko_1", "source/image/ui/scene/kyoko_1.bmp", 386, 460, true, MAGENTA);
	IMG_M->addImage("kyoko_2", "source/image/ui/scene/kyoko_2.bmp", 386, 460, true, MAGENTA);
	IMG_M->addImage("kyoko_3", "source/image/ui/scene/kyoko_3.bmp", 386, 460, true, MAGENTA);
	IMG_M->addImage("misuzu_1", "source/image/ui/scene/misuzu_1.bmp", 386, 460, true, MAGENTA);
	IMG_M->addImage("misuzu_2", "source/image/ui/scene/misuzu_2.bmp", 386, 460, true, MAGENTA);
	IMG_M->addImage("misuzu_3", "source/image/ui/scene/misuzu_3.bmp", 386, 460, true, MAGENTA);

	//================= UI =================
	IMG_M->addImage("shadow", "source/image/character/shadow.bmp", 128, 38, true, MAGENTA, true);
	IMG_M->addImage("bossHPBack", "source/image/ui/battle/boss_HP_back.bmp", 898, 120, true, MAGENTA);
	IMG_M->addImage("bossHPFront", "source/image/ui/battle/boss_HP_front.bmp", 898, 120, true, MAGENTA);
	IMG_M->addImage("save_load_close", "source/image/ui/scene/save_load_close.bmp", 365, 150, true, MAGENTA);
	IMG_M->addImage("save_load_open", "source/image/ui/scene/save_load_open.bmp", 365, 150, true, MAGENTA);
	IMG_M->addImage("UI_kyoko", "source/image/ui/scene/UI_Kyoko_Portrait.bmp", 120, 135, true, MAGENTA);
	IMG_M->addImage("UI_Locked_Door", "source/image/ui/battle/UI_Locked_Door.bmp", 52, 76, true, MAGENTA);
	IMG_M->addImage("UI_UnLocked_Door", "source/image/ui/battle/UI_UnLocked_Door.bmp", 52, 76, true, MAGENTA);

	IMG_M->addImage("phone", "source/image/ui/inven/phone.bmp", 480, 642, true, MAGENTA);
	//================= 스테이지 =================
	IMG_M->addImage("easyStage", "source/image/stage/easy.bmp", 2028, 678, false, MAGENTA);
	IMG_M->addImage("normalStage", "source/image/stage/normal.bmp", 2865, 837, false, MAGENTA);
	IMG_M->addImage("hardStage", "source/image/stage/hard.bmp", 2328, 1428, false, MAGENTA);
	IMG_M->addImage("bossStage", "source/image/stage/boss1.bmp", 3116, 1215, false, MAGENTA);
	IMG_M->addImage("bossStage2", "source/image/stage/boss2.bmp", 3116, 1215, false, MAGENTA);

	//================= 플래이어 =================
	IMG_M->addFrameImage("pl_climb", "source/image/character/player/climb.bmp", 720, 237, 6, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_climbTop", "source/image/character/player/climbTop.bmp", 288, 192, 3, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("pl_climbTopDown", "source/image/character/player/climbTopDown.bmp", 288, 234, 3, 1, true, MAGENTA, true);
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
	//===============여자학생==========================
	IMG_M->addFrameImage("schoolGirlIdle", "source/image/character/enemy/schoolGirl/Idle.bmp", 1170, 354, 10,2,true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlWalk", "source/image/character/enemy/schoolGirl/walk.bmp", 1296, 372, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlRun", "source/image/character/enemy/schoolGirl/run.bmp", 1470, 330, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlJump", "source/image/character/enemy/schoolGirl/jump.bmp", 342, 366, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlLadder", "source/image/character/enemy/schoolGirl/ladder.bmp", 594, 219, 6, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlLadderTransition", "source/image/character/enemy/schoolGirl/transition.bmp", 387, 168, 3, 1, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolGirlPatrol", "source/image/character/enemy/schoolGirl/.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlStun", "source/image/character/enemy/schoolGirl/stun.bmp", 456, 324, 4, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlBegging", "source/image/character/enemy/schoolGirl/begging.bmp", 378, 336, 3, 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolGirlDie", "source/image/character/enemy/schoolGirl/.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlGuard", "source/image/character/enemy/schoolGirl/block.bmp", 351, 337, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlHeldRelease", "source/image/character/enemy/schoolGirl/HeldRelease.bmp", 528, 360, 4, 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolGirlFriend", "source/image/character/enemy/schoolGirl/.bmp", , , , 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolGirlRunAttack", "source/image/character/enemy/schoolGirl/attack1.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlJumpAttack", "source/image/character/enemy/schoolGirl/jumpAttack.bmp", 1197, 354, 7, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlHardAttack", "source/image/character/enemy/schoolGirl/comboAttack3.bmp", 2412, 414, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlAttack1", "source/image/character/enemy/schoolGirl/comboAttack1.bmp", 1239, 354, 7, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlAttack2", "source/image/character/enemy/schoolGirl/comboAttack2.bmp", 2208, 354, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlAttack3", "source/image/character/enemy/schoolGirl/comboAttack3.bmp", 2412, 414, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlDown", "source/image/character/enemy/schoolGirl/backdown.bmp", 6939, 376, 27, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlHeldHit", "source/image/character/enemy/schoolGirl/HeldHit.bmp", 576, 336, 4, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlHit", "source/image/character/enemy/schoolGirl/gethit.bmp", 1431, 360, 9, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlWeaponHit", "source/image/character/enemy/schoolGirl/weaponhit.bmp", 4369, 336, 17, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlWAttack", "source/image/character/enemy/schoolGirl/WAttack.bmp", 1580, 558, 5, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlWIdle", "source/image/character/enemy/schoolGirl/WIdle.bmp", 1950, 408, 10, 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolGirlWPickup", "source/image/character/enemy/schoolGirl/.bmp", 1170, 354, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlWRun", "source/image/character/enemy/schoolGirl/WRun.bmp", 1880, 458, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlWThrow", "source/image/character/enemy/schoolGirl/WThrow.bmp", 1488, 540, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlWWalk", "source/image/character/enemy/schoolGirl/WWalk.bmp", 2232, 502, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolGirlWJump", "source/image/character/enemy/schoolGirl/WJump.bmp", 429, 450, 3, 2, true, MAGENTA, true);

	//====================남자학생=======================
	IMG_M->addFrameImage("schoolBoyIdle", "source/image/character/enemy/schoolBoy/Idle.bmp", 1224, 432, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyWalk", "source/image/character/enemy/schoolBoy/walk.bmp", 1620, 444, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyRun", "source/image/character/enemy/schoolBoy/run.bmp", 1920, 390, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyJump", "source/image/character/enemy/schoolBoy/jump.bmp", 423, 486, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyLadder", "source/image/character/enemy/schoolBoy/ladder.bmp", 738, 264, 6, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyLadderTransition", "source/image/character/enemy/schoolBoy/transition.bmp", 405, 183, 3, 1, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolBoyPatrol", "source/image/character/enemy/schoolBoy/.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyStun", "source/image/character/enemy/schoolBoy/stun.bmp", 633, 408, 4, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyBegging", "source/image/character/enemy/schoolBoy/begging.bmp", 216, 354, 2, 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolBoyDie", "source/image/character/enemy/schoolBoy/.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyGuard", "source/image/character/enemy/schoolBoy/block.bmp", 459, 438, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyHeldRelease", "source/image/character/enemy/schoolBoy/HeldRelease.bmp", 660, 480, 4, 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolBoyFriend", "source/image/character/enemy/schoolBoy/.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyRunAttack", "source/image/character/enemy/schoolBoy/attack1.bmp", 1920, 390, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyJumpAttack", "source/image/character/enemy/schoolBoy/jumpAttack.bmp", 1224, 468, 6, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyHardAttack", "source/image/character/enemy/schoolBoy/comboAttack3.bmp", 1890, 558, 9, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyAttack1", "source/image/character/enemy/schoolBoy/comboAttack1.bmp", 2352, 426, 7, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyAttack2", "source/image/character/enemy/schoolBoy/comboAttack2.bmp", 1757, 444, 7, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyAttack3", "source/image/character/enemy/schoolBoy/comboAttack3.bmp", 1890, 558, 9, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyDown", "source/image/character/enemy/schoolBoy/backdown.bmp", 7695, 438, 27, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyHeldHit", "source/image/character/enemy/schoolBoy/HeldHit.bmp", 576, 372, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyHit", "source/image/character/enemy/schoolBoy/gethit.bmp", 1728, 450, 9, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyWeaponHit", "source/image/character/enemy/schoolBoy/weaponhit.bmp", 5415, 438, 19, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyWAttack", "source/image/character/enemy/schoolBoy/WAttack.bmp", 1830, 660, 5, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyWIdle", "source/image/character/enemy/schoolBoy/WIdle.bmp", 1224, 552, 8, 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolBoyWPickup", "source/image/character/enemy/schoolBoy/.bmp", 1170, 354, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyWRun", "source/image/character/enemy/schoolBoy/WRun.bmp", 2250, 516, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyWThrow", "source/image/character/enemy/schoolBoy/WThrow.bmp", 1752, 564, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyWWalk", "source/image/character/enemy/schoolBoy/WWalk.bmp", 1572, 556, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolBoyWJump", "source/image/character/enemy/schoolBoy/WJump.bmp", 432, 468, 3, 2, true, MAGENTA, true);

	//===============응원단장=============================
	IMG_M->addFrameImage("schoolCheerIdle", "source/image/character/enemy/cheerLeader/Idle.bmp", 2304, 432, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerWalk", "source/image/character/enemy/cheerLeader/walk.bmp", 2736, 438, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerRun", "source/image/character/enemy/cheerLeader/run.bmp", 1368, 318, 8, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerJump", "source/image/character/enemy/cheerLeader/jump.bmp", 540, 474, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerLadder", "source/image/character/enemy/cheerLeader/ladder.bmp", 900, 255, 6, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerLadderTransition", "source/image/character/enemy/cheerLeader/transition.bmp", 396, 186, 3, 1, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolCheerPatrol", "source/image/character/enemy/cheerLeader/.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerStun", "source/image/character/enemy/cheerLeader/stun.bmp", 540, 390, 4, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerBegging", "source/image/character/enemy/cheerLeader/begging.bmp", 513, 372, 3, 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolCheerDie", "source/image/character/enemy/cheerLeader/.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerGuard", "source/image/character/enemy/cheerLeader/block.bmp", 489, 428, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerHeldRelease", "source/image/character/enemy/cheerLeader/HeldRelease.bmp", 840, 456, 4, 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolCheerFriend", "source/image/character/enemy/cheerLeader/.bmp", , , , 2, true, MAGENTA, true);
	//IMG_M->addFrameImage("schoolCheerRunAttack", "source/image/character/enemy/cheerLeader/attack1.bmp", , , , 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerJumpAttack", "source/image/character/enemy/cheerLeader/jumpAttack.bmp", 1491, 654, 7, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerHardAttack", "source/image/character/enemy/cheerLeader/comboAttack3.bmp", 4050, 498, 15, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerAttack1", "source/image/character/enemy/cheerLeader/comboAttack1.bmp", 1332, 468, 6, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerAttack2", "source/image/character/enemy/cheerLeader/comboAttack2.bmp", 1827, 426, 7, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerAttack3", "source/image/character/enemy/cheerLeader/comboAttack3.bmp", 4050, 498, 15, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerDown", "source/image/character/enemy/cheerLeader/backdown.bmp", 9338, 436, 29, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerHeldHit", "source/image/character/enemy/cheerLeader/HeldHit.bmp", 840, 384, 5, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerHit", "source/image/character/enemy/cheerLeader/gethit.bmp", 1539, 426, 9, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("schoolCheerWeaponHit", "source/image/character/enemy/cheerLeader/weaponhit.bmp", 7084, 436, 22, 2, true, MAGENTA, true);


	//================= 보스 ====================
	IMG_M->addFrameImage("Bs_idle", "source/image/character/enemy/boss/idle.bmp", 3180, 634, 12, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_move", "source/image/character/enemy/boss/move.bmp", 2110, 588, 10, 2, true, MAGENTA, true);
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
	IMG_M->addFrameImage("Bs_dash2", "source/image/character/enemy/boss/dash.bmp", 2619, 582, 10, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_meteordown", "source/image/character/enemy/boss/meteor.bmp", 480, 460, 2, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_attacked1", "source/image/character/enemy/boss/attacked 01.bmp", 737, 594, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_attacked2", "source/image/character/enemy/boss/attacked 02.bmp", 737, 594, 3, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("Bs_attacked3", "source/image/character/enemy/boss/attacked 03.bmp", 737, 598, 3, 2, true, MAGENTA, true);


	//================= 보스 이펙트===============
	EFFECT_M->addEffect("Bss_attack", "attack.bmp", 612, 196, 204, 196, 1.f, 3.f, 50);
	EFFECT_M->addEffect("Bss_smash", "Boss smash.bmp", 960, 89, 96, 89, 1.f, 3.f, 50);
	EFFECT_M->addEffect("Bss_howling", "Boss howling.bmp", 1821, 165,227.f, 165, 1.f, 3.f, 100);
	EFFECT_M->addEffect("Bss_howling2", "Boss howling2.bmp", 416, 208, 208, 208, 1.f, 3.f, 50);
	EFFECT_M->addEffect("Bss_meteor", "Boss meteor2.bmp", 2424, 320, 404, 320, 1.f, 3.f, 50);
	EFFECT_M->addEffect("Bss_crush", "crush.bmp", 190, 193, 190, 193, 1.f, 3.f, 50);
	EFFECT_M->addEffect("Bss_stand", "Boss stand2.bmp", 3390, 144, 484.2f, 144, 1.f, 3.f, 50);
	EFFECT_M->addEffect("Bss_phase", "Boss phase1.bmp", 299, 82, 99.6f, 82, 1.f, 3.f, 50);
	EFFECT_M->addEffect("Bss_stun", "stun.bmp", 420, 54, 70, 54, 1.f, 3.f, 50);
	EFFECT_M->addEffect("Ob_break", "obj break.bmp", 3304, 248, 236, 248, 1.f, 3.f, 50);
	
	//================= 오브젝트 =================

	IMG_M->addImage("desk", "source/image/object/desk.bmp", 147, 162, true, MAGENTA, true);
	IMG_M->addImage("table", "source/image/object/table.bmp", 339, 162, true, MAGENTA, true);
	IMG_M->addFrameImage("vendingMachine", "source/image/object/vendingMachine.bmp", 525, 260, 2, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("pillar", "source/image/object/pillar.bmp", 390, 678, 2, 1, true, MAGENTA, true);
	IMG_M->addFrameImage("pillar_big", "source/image/object/pillar_big.bmp", 390, 957, 2, 1, true, MAGENTA, true);
	IMG_M->addImage("pillar_particle_1", "source/image/object/pillar_particle_1.bmp", 64, 64, true, MAGENTA, true);
	IMG_M->addImage("pillar_particle_2", "source/image/object/pillar_particle_2.bmp", 64, 64, true, MAGENTA, true);
	IMG_M->addImage("pillar_particle_3", "source/image/object/pillar_particle_3.bmp", 64, 64, true, MAGENTA, true);

	IMG_M->addFrameImage("bat", "source/image/object/bat.bmp", 179, 104, 1, 2, true, MAGENTA, true);
	IMG_M->addFrameImage("pet", "source/image/object/pet.bmp", 576, 96, 6, 1, true, MAGENTA, true);
	//================= 아이템 =================
	IMG_M->addImage("meat", "source/image/item/meat.bmp", 60, 51, true, MAGENTA, true);
	IMG_M->addImage("apple", "source/image/object/apple.bmp", 50, 50, true, MAGENTA, true);
	IMG_M->addImage("chili", "source/image/object/chili.bmp", 50, 50, true, MAGENTA, true);
	IMG_M->addImage("hen", "source/image/object/hen.bmp", 50, 50, true, MAGENTA, true);

	IMG_M->addFrameImage("money", "source/image/object/money_green.bmp", 256, 192, 4, 3, true, MAGENTA, true);
	IMG_M->addFrameImage("coin", "source/image/object/gold_coin_spin.bmp", 256, 256, 4, 4, true, MAGENTA, true);

	//================= 이팩트 =================
	EFFECT_M->addEffect("ef_attack", "attack.bmp", 612, 196, 204, 196, 1.f, .15f, 50);
	EFFECT_M->addEffect("ef_beg", "beg.bmp", 268, 127, 134, 127, 1.f, 3.f, 20);
	EFFECT_M->addEffect("ef_blueAttack", "blueAttack.bmp", 1440, 160, 160, 160, 1.f, .25f, 50);
	EFFECT_M->addEffect("ef_explosion", "explosion.bmp", 2701, 247, 385, 247, 1.f, .15f, 50);
	EFFECT_M->addEffect("ef_runL", "runL.bmp", 2784, 126, 232, 126, 1.f, .3f, 20);
	EFFECT_M->addEffect("ef_runR", "runR.bmp", 2784, 126, 232, 126, 1.f, .3f, 20);
	EFFECT_M->addEffect("ef_shake", "shake.bmp", 268, 127, 134, 127, 1.f, 3.f, 20);
	EFFECT_M->addEffect("ef_spark", "spark.bmp", 512, 128, 128, 128, 1.f, .2f, 20);	
	EFFECT_M->addEffect("ef_star", "star.bmp", 1350, 90, 90, 90, 1.f, .2f, 20);
	EFFECT_M->addEffect("ef_stun", "stun.bmp", 420, 54, 70, 54, 1.f, .07f, 20);
	EFFECT_M->addEffect("ef_point", "point.bmp", 560, 70, 70, 70, 1.f, .1f, 20);
}

