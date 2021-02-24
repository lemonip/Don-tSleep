#pragma once
#include "singletonBase.h"
#include <bitset>
#include <vector>

#define KEYMAX 256

using namespace std;

class keyManager : public singletonBase <keyManager>
{
private:
	bitset<KEYMAX> _keyUp;
	bitset<KEYMAX> _keyDown;
	vector<int> _vKeyComendBuffer;			//ŰĿ�ǵ�����
	SHORT _KeyBuffer;						//���� Ű ����
public:
	keyManager();
	~keyManager();

	HRESULT init();
	void release();

	//Ű�� �� ���� �����ٸ�
	bool isOnceKeyDown(int key);

	//Ű�� �� ���� �����ٸ� ���������
	bool isOnceKeyDownV(int key);

	//Ű�� �����ٰ� ����
	bool isOnceKeyUp(int key);

	//Ű�� ��� ������ ������
	bool isStayKeyDown(int key);

	//Ű�� ��۵Ǹ�(?) 
	bool isToggleKey(int key);



	bitset<KEYMAX> getKeyUp() { return _keyUp; }
	bitset<KEYMAX> getKeyDown() { return _keyDown; }
	//Ű���͸� �����´�
	vector<int> getVKeyBuffer() { return _vKeyComendBuffer; }
	//Ű������ �ֱ��ε������� -num�� �ε����� ���� ��ȯ�Ѵ�.
	int getKeyBuffer(int num) { return _vKeyComendBuffer[_vKeyComendBuffer.size() - num - 1]; }

	void setKeyDown(int key, bool state) { _keyDown.set(key, state); }
	void setKeyUp(int key, bool state) { _keyUp.set(key, state); }
	//���� Ű ���͸� ��� �����.
	void clearVKey();

};

