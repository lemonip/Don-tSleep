#include "stdafx.h"
#include "DataManager.h"

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

void DataManager::updateStageData(Player* player)
{
	_stageData._playerData = player;

}
