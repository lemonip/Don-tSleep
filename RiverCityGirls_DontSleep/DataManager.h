#pragma once
#include "singletonBase.h"


class Player;
class StageManager;

// 무슨 데이터를 가지고 있어야하나?
struct tagSaveLoadData
{
	string PosX;
	string PosY;
	string PosZ;
	string HP;
	string MaxHP;
	string Force;
	string Coin;
	string LV;
	string EXP;

	string CurrentStage;
	string easyLockEvent;
	string normalLockEvent;
	string hardLockEvent;
};	




class DataManager : public singletonBase<DataManager>
{
	struct tagStageData
	{
		// player
		vector3 playerPos;
		int hp;
		int maxHP;
		int force;
		float coin;
		int LV;
		float exp;

		// stage
		int curStage;
		bool easyLockEventEnd;
		bool normalLockEventEnd;
		bool hardLockEventEnd;
		tagStageData()
		{
			curStage = 0;
			easyLockEventEnd = 0;
			normalLockEventEnd = 0;
			hardLockEventEnd = 0;
		}
	};


private:
	typedef vector<tagSaveLoadData>						arrSaveLoadData;
	typedef vector<tagSaveLoadData>::iterator			arrSaveLoadIter;

	typedef vector<arrSaveLoadData>					vSaveLoadDataList;
	typedef vector<arrSaveLoadData>::iterator		vSaveLoadDataIter;
private:
	vSaveLoadDataList _vDatas;
	tagStageData _data;

	Player* _player;
	StageManager* _stageM;
public:
	DataManager();
	~DataManager();

	HRESULT init();
	void release();

	//데이터 추가 함수
	void addData();
	//ini파일 만들어주는 함수
	void saveIniData(int num);
	bool loadIniData(int num);

	void saveStageData();
	void loadStageData();



	void checkData();
	void setPlayerHP(int num);
	void plusPlayerHP(int num);
	bool minusPlayerCoin(float numf);
	void setLinkPlayer(Player* player);
	void setLinkStageM(StageManager* stageM);

	
};

