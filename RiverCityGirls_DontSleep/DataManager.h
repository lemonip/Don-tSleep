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
	int playerHp;
	vector3 playerPos;
	bool eventEnd;



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


public:
	DataManager();
	~DataManager();

	HRESULT init();

	//데이터 추가 함수
	void addData(const char* subject, const char* title, const char* body);
	//ini파일 만들어주는 함수
	void iniSave(const char* fileName);

	//문자열 데이터 불러오는 함수
	string loadDataString(const char* fileName, const char* subject, const char* title);

	//정수 데이터 불러오는 함수
	int loadDataInterger(const char* fileName, const char* subject, const char* title);

	

};

