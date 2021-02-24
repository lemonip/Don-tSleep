#pragma once


/*====================================================================
							���� ���� ��ƿ
====================================================================*/
class Interpolation
{
private:
	vector3* _pos;
	float _startX, _startY;
	float _endX, _endY;

	float _angle;
	float _travelRange;
	float _worldTimeCount;
	float _time;

	bool _isMoving;

public:
	Interpolation();
	~Interpolation() {};

	//������Ʈ
	void update();
	
	//n�� ���� x,y�� ���� ������
	void moveTo(vector3* pos, float endX, float endY, float time);

	//�����̴� ��
	void moving();

	//Getter
	bool getIsMoving() { return _isMoving; }

};

