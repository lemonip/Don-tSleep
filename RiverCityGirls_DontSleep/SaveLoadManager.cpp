#include "stdafx.h"
#include "SaveLoadManager.h"
#pragma warning(disable:4996)


void SaveLoadManager::update()
{
	if (KEY_M->isOnceKeyDown(VK_F1))
	{
		save();
	}
	if (KEY_M->isOnceKeyDown(VK_F2))
	{
		load();
	}
}

void SaveLoadManager::save()
{

}

void SaveLoadManager::load()
{

}

void SaveLoadManager::pushData(vector<string>* vector, int x)
{
	char temp[128];
	(*vector).push_back(itoa(x, temp, 10));
}
