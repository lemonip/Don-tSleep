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
	IMG_M->addFrameImage("kyoko", "source/image/character/player/idle.bmp", 1440, 450, 12, 2,true, MAGENTA, true);

	//================= 에너미 =================
	IMG_M->addFrameImage("schoolGirl", "source/image/character/enemy/schoolGirl/idle.bmp", 1170, 354, 10,2,true, MAGENTA, true);

	//================= 오브젝트 =================
	IMG_M->addImage("desk", "source/image/object/desk.bmp", 98, 108, true, MAGENTA, true);

	//================= 아이템 =================
	IMG_M->addImage("meat", "source/image/item/meat.bmp", 60, 51, true, MAGENTA, true);
}