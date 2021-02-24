#pragma once
#include "singletonBase.h"
#include <string>
#include <map>

class gameNode;

class SceneManager : public singletonBase<SceneManager>
{
public:
	typedef map<string, gameNode*> mapSceneList;
	typedef map<string, gameNode*>::iterator mapSceneIter;

private:
	gameNode* _prevScene;
	static gameNode* _currentScene;

	mapSceneList _mSceneList;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���߰� �Լ�
	gameNode* addScene(string sceneName, gameNode* scene);

	//������, �̴��ϸ� ���� �����ϴ� �Լ�
	HRESULT changeScene(string sceneName);

	//�̴����� �ʰ� ���� �����ϴ� �Լ�
	HRESULT setScene(string sceneName);
	
	//�̴��ϰ� ���� ����
	HRESULT setInitScene(string sceneName);

	//���� ������ ���ư�
	HRESULT setPrevScene();

	SceneManager() {};
	~SceneManager() {};
};

