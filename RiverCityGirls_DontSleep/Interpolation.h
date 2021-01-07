#pragma once

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

	void update();

	void moveTo(vector3* pos, float endX, float endY, float time);

	void moving();

	bool getIsMoving() { return _isMoving; }

};

