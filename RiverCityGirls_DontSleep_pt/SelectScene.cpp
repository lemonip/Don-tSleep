#include "stdafx.h"
#include "SelectScene.h"
#include <string>

HRESULT SelectScene::init()
{
	/*====================================================================
		���� ������ ���̺� ������ �ε��� �� �ְ� �մϴ�.
		���̺� ����, ĳ���� ����, �ɼ�, �޴��� â �� ���� ���� ���� ��� ������ �մϴ�.
	====================================================================*/

	/*====================================================================
		���� ����� �����ϰ�, Ÿ��Ʋ�� UI�� ����ϸ�, ����� ������ŵ�ϴ�.
	====================================================================*/
	_background = IMG_M->findImage("select_background");
	CAMERA_M->SetMap(*this, WINSIZEX, WINSIZEY);
	loop = vector3(0, 0, 0);
	_background2 = IMG_M->findImage("select_background2");

	/*====================================================================
		�� ĳ���� �̹����� ���� �������� �̵���ŵ�ϴ�.
	====================================================================*/
	_illust = IMG_M->findImage("select_illust");
	_illustPos = vector3(350.0f, WINSIZEY / 2 + 360.0f, 0.0f);
	_illustInter = new Interpolation;
	_illustInter->moveTo(&_illustPos, 450, WINSIZEY / 2 + 360, 0.5f);
	_ratioOffset = 0.001f;

	/*====================================================================
		UI�� ���� �̹����� �߰��ϰ�, ������ �� �ֵ��� �մϴ�.
	====================================================================*/
	int _loadNum[4];

	for (int i = 0; i < 4; i++)
	{
		_loadNum[i] = DATA_M->getStage(i);
	}

	//�ε� ���� ���� ��ư
	_loadSelect = new Select;

	string txt1;
	string txt2;


	txt1 = "save_load_close" + to_string(_loadNum[0] + 1);
	txt2 = "save_load_open" + to_string(_loadNum[0] + 1);
	_loadSelect->addButton(Button(IMG_M->findImage(txt1), IMG_M->findImage(txt2), vector3(900, (WINSIZEY - 150) / 4 * 1, 0), std::bind(&SelectScene::load0, this), 0));

	txt1 = "save_load_close" + to_string(_loadNum[1] + 1);
	txt2 = "save_load_open" + to_string(_loadNum[1] + 1);
	_loadSelect->addButton(Button(IMG_M->findImage(txt1), IMG_M->findImage(txt2), vector3(900, (WINSIZEY - 150) / 4 * 2, 0), std::bind(&SelectScene::load1, this), 1));

	txt1 = "save_load_close" + to_string(_loadNum[2] + 1);
	txt2 = "save_load_open" + to_string(_loadNum[2] + 1);
	_loadSelect->addButton(Button(IMG_M->findImage(txt1), IMG_M->findImage(txt2), vector3(900, (WINSIZEY - 150) / 4 * 3, 0), std::bind(&SelectScene::load2, this), 2));

	txt1 = "save_load_close" + to_string(_loadNum[3] + 1);
	txt2 = "save_load_open" + to_string(_loadNum[3] + 1);
	_loadSelect->addButton(Button(IMG_M->findImage(txt1), IMG_M->findImage(txt2), vector3(900, (WINSIZEY - 150) / 4 * 4, 0), std::bind(&SelectScene::load3, this), 3));


	//ĳ���� ���� ��ư�� �̹���
	_charSelect = new Select;
	_charSelect->addButton(Button(IMG_M->findImage("select_kyoko2"), IMG_M->findImage("select_kyoko"), vector3(WINSIZEX/2 + 100, WINSIZEY / 2, 0), std::bind(&SelectScene::character0, this), 0));
	_charSelect->addButton(Button(IMG_M->findImage("select_misako2"), IMG_M->findImage("select_misako"), vector3(WINSIZEX/2 + 450, WINSIZEY / 2, 0), std::bind(&SelectScene::character1, this), 1));
	_kyokoSelect = false;

	//�ɼ� UI�� ��ư


	//�޴��� UI�� ��ư


	/*====================================================================
		ù ���¸� �ε�� �����մϴ�. LOAD - OPTION - MANUAL �Ŀ� �ε������� �̾����ϴ�.
	====================================================================*/
	setState(SELECTTYPE::LOAD);

	return S_OK;
}

void SelectScene::release()
{
}

void SelectScene::update()
{
	/*====================================================================
		ĳ���� �Ϸ���Ʈ�� �̵��� Ȯ�� ��� ȿ���� �����ϰ�
		����� x+1, y+1 �밢�� �������� ���� ��ŵ�ϴ�.
	====================================================================*/
	loop.x++; loop.y++;

	_illustInter->update();
	_ratioOffset = (TIME_M->getWorldTime() - _ratioTime) * 0.04f;
	if (TIME_M->getWorldTime() - _ratioTime > 0.35f) _ratioTime = TIME_M->getWorldTime();

	/*====================================================================
		ī�޶�� �߾ӿ� ������Ű��, ���͸� ġ�� ���� ������ �ѱ�ϴ�.
	====================================================================*/
	CAMERA_M->SetPos(WINSIZEX / 2, WINSIZEY / 2);

	/*====================================================================

	====================================================================*/
	switch (_state)
	{
		/*====================================================================
			��ư�� �����ϰ�, ������ �� �Ŀ��� ĳ���� �������� �Ѿ�ϴ�.
		====================================================================*/
		case SELECTTYPE::LOAD:
		if (_loadSelect->update()) setState(SELECTTYPE::CHARACTER);
		break;

		/*====================================================================
			ĳ���͸� �����ϰ�, �ɼ�â���� �Ѿ�ϴ�.
		====================================================================*/
		case SELECTTYPE::CHARACTER:
		_charSelect->update();
		if(_kyokoSelect) setState(SELECTTYPE::MANUAL);
		break;
		/*====================================================================
			�޴��� UI�� ����, ���� �ε������� �����մϴ�.
		====================================================================*/
		case SELECTTYPE::MANUAL:
		if (!EVENT_M->getIsEvent())
		{
			if ((KEY_M->isOnceKeyDown(VK_RETURN) || KEY_M->isOnceKeyDown(VK_SPACE)))
			{
				SCENE_M->changeScene("loading");			//�ε� ������ ����
			}
		}
		break;
		default:
		break;
	}
}

void SelectScene::render()
{
	/*====================================================================
		����� loop ���� ���� ���� �����ϰ�, ĳ���� �̹����� ��� �ݴϴ�.
	====================================================================*/
	
	switch (_state)
	{
	case SELECTTYPE::LOAD: case SELECTTYPE::CHARACTER:
		_background->loopRender(getMapDC(), &CAMERA_M->GetScreenRect(), loop.x, loop.y);
		_background2->render(getMapDC());
		IMG_M->findImage("start_frame")->render(getMapDC(), 800, 450, 1280 / 1600.0f, 720 / 900.0f);
		_illust->render(getMapDC(), _illustPos.x - _illustPos.x*_ratioOffset, _illustPos.y - _illustPos.y *_ratioOffset, 0.7f + _ratioOffset, 0.7f + _ratioOffset);

		break;
	case SELECTTYPE::MANUAL:
		IMG_M->findImage("SelectScene_manual")->render(getMapDC());

		break;
	default:
		break;
	}

	/*====================================================================
		UI �� �ؽ�Ʈ�� ����մϴ�.
	====================================================================*/
	switch (_state)
	{
		case SELECTTYPE::LOAD:
		{
			_loadSelect->render(getMapDC());

		}
		break;
		case SELECTTYPE::CHARACTER:
			IMG_M->findImage("select_kyoko_background")->render(getMapDC(), WINSIZEX / 2 + 100, WINSIZEY / 2);
			IMG_M->findImage("select_misako_background")->render(getMapDC(), WINSIZEX / 2 + 450, WINSIZEY / 2);
			_charSelect->render(getMapDC());
		break;
		case SELECTTYPE::MANUAL:
		{
			//��Ʈ�� ���� �����Ѵ�.
			SetBkMode(getMapDC(), TRANSPARENT);
			SetTextColor(getMapDC(), RGB(0, 0, 0));
			HFONT font, oldFont;
			RECT rcText = RectMake(WINSIZEX/2, 120, 400, 720);
			font = CreateFont(50, 0, 0, 0, 0, false, false, false,
				DEFAULT_CHARSET, OUT_STRING_PRECIS, CLIP_DEFAULT_PRECIS,
				PROOF_QUALITY, DEFAULT_PITCH | FF_SWISS, TEXT("CookieRunOTF Bold"));
			oldFont = (HFONT)SelectObject(getMapDC(), font);

			string _txt = "�̵�: ����Ű / ����: A \n���: S / ����: D \nĿ�ǵ����: �� + �� + D \n����: F / ȸ��:W \n�ݱ�:E / ����:Q \n�κ�: V / �� �̵� : M \n���� : SPACEBAR or ENTER / ���� : ESC \n����� : SHIFT or TAB" ;
			
			//�ؽ�Ʈ�� ����Ѵ�.
			DrawText(getMapDC(), TEXT(_txt.c_str()), strlen(_txt.c_str()), &rcText, DT_LEFT | DT_WORDBREAK | DT_VCENTER);
			//��Ʈ�� �����Ѵ�.
			DeleteObject(font);
		}
		break;
		default:
		break;
	}
}

/*====================================================================
	��ư ���ÿ� ���� ���̺� ������ �ε��մϴ�.
====================================================================*/
void SelectScene::load(int n)
{
	DATA_M->setFileNum(n);
	DATA_M->loadIniData(n);
}
void SelectScene::load0()
{
	load(0);
}
void SelectScene::load1()
{
	load(1);
}
void SelectScene::load2()
{
	load(2);
}
void SelectScene::load3()
{
	load(3);
}

/*====================================================================
	��ư ���ÿ� ���� ĳ���͸� �ε��մϴ�.
====================================================================*/
void SelectScene::character0()
{
	_kyokoSelect = true;
}

void SelectScene::character1()
{
	_kyokoSelect = false;
	_charSelect = new Select;
	_charSelect->addButton(Button(IMG_M->findImage("select_kyoko2"), IMG_M->findImage("select_kyoko"), vector3(WINSIZEX / 2 + 100, WINSIZEY / 2, 0), std::bind(&SelectScene::character0, this), 0));
	_charSelect->addButton(Button(IMG_M->findImage("select_misako2"), IMG_M->findImage("select_misako"), vector3(WINSIZEX / 2 + 450, WINSIZEY / 2, 0), std::bind(&SelectScene::character1, this), 1));
	_charSelect->_index = 1;
}

/*====================================================================
	���� ���� ���¸� �����մϴ�.
====================================================================*/
void SelectScene::setState(SELECTTYPE type)
{
	_state = type;

	switch (_state)
	{
		case SELECTTYPE::LOAD:
		break;
		case SELECTTYPE::CHARACTER:
		break;
		case SELECTTYPE::MANUAL:
		break;
		default:
		break;
	}
	/*====================================================================
		ȭ�� ���°� �ٲ� ������ ī�޶� �����Ӱ� ��� �̺�Ʈ�� �����մϴ�.
	====================================================================*/
	EVENT_M->addEvent(new waitForSec(0.3f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.1f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.05, 0.005f));
	EVENT_M->addEvent(new waitForSec(0.2f));
	EVENT_M->addEvent(new cameraMove(vector3(0, 0, 0), 5, 1.0, 0.005f));
}
