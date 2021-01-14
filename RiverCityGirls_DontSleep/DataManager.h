#pragma once
#include "singletonBase.h"

class Player;
class StageManager;

// 무슨 데이터를 가지고 있어야하나?
struct tagSaveLoadData
{
	const char* subject;
	const char* title;
	const char* body;
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
		bool lockEventEnd;
	};


private:
	typedef vector<tagSaveLoadData>					arrSaveLoadData;
	typedef vector<tagSaveLoadData>::iterator		arrSaveLoadIter;

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

	//데이터 추가 함수
	void addData(const char* subject, const char* title, const char* body);
	//ini파일 만들어주는 함수
	void iniSave(const char* fileName);

	void saveStageData(Player* player, StageManager* stage);
	void loadStageData(Player* player, StageManager* stage);
	void loadStageData();
	//문자열 데이터 불러오는 함수
	string loadDataString(const char* fileName, const char* subject, const char* title);

	//정수 데이터 불러오는 함수
	int loadDataInterger(const char* fileName, const char* subject, const char* title);

	void checkData();
	void setPlayerHP(int num);
	void plusPlayerHP(int num);
	bool minusPlayerCoin(float numf);
	void setLinkPlayer(Player* player);
	void setLinkStageM(StageManager* stageM);
};

