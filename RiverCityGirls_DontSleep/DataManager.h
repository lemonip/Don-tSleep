#pragma once
#include "singletonBase.h"

// 무슨 데이터를 가지고 있어야하나?
struct tagSaveLoadData
{
	const char* subject;
	const char* title;
	const char* body;
};

struct tagStageData
{
	Player* _playerData;
	// 추후에 데이터 추가(인벤토리?)


};


class DataManager : public singletonBase<DataManager>
{
private:
	typedef vector<tagSaveLoadData>					arrSaveLoadData;
	typedef vector<tagSaveLoadData>::iterator		arrSaveLoadIter;

	typedef vector<arrSaveLoadData>					vSaveLoadDataList;
	typedef vector<arrSaveLoadData>::iterator		vSaveLoadDataIter;
private:
	vSaveLoadDataList _vDatas;

	tagStageData _stageData;

public:
	DataManager();
	~DataManager();

	HRESULT init();

	// 데이터 추가?
	void updateStageData(Player* player);

};

