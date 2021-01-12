#include "stdafx.h"
#include "DataManager.h"
#include "Player.h"

DataManager::DataManager()
{
}

DataManager::~DataManager()
{
}

HRESULT DataManager::init()
{
	return S_OK;
}

void DataManager::addData(const char * subject, const char * title, const char * body)
{
	// 데이터 추가
}

void DataManager::iniSave(const char * fileName)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	strncat_s(str, 256, dir, 254);

	for (int i = 0; i < _vDatas.size(); ++i)
	{
		arrSaveLoadData data = _vDatas[i];
		WritePrivateProfileString(data[0].subject, data[0].title, data[0].body, str);
		data.clear();
	}

	_vDatas.clear();
}

string DataManager::loadDataString(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);

	char data[64] = {};
	GetPrivateProfileString(subject, title, "", data, 64, str);

	string strData = data;


	return strData;
}

int DataManager::loadDataInterger(const char * fileName, const char * subject, const char * title)
{
	char str[256];
	char dir[256];

	ZeroMemory(dir, sizeof(dir));
	sprintf_s(dir, "\\%s.ini", fileName);

	GetCurrentDirectory(256, str);
	strncat_s(str, 256, dir, 254);


	return GetPrivateProfileInt(subject, title, 0, str);
}








