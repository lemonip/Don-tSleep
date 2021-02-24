#pragma once

/*====================================================================
							x,y,z ����3 ��ƿ
====================================================================*/

class vector3
{
public:
	float x, y, z;

public:
	vector3() {}
	vector3(float x, float y, float z);
	vector3(int x, int y, int z);
	~vector3() {}

	// ======================= getter =======================

	int getIntX() { return (int)(this->x); }
	int getIntY() { return (int)(this->y); }
	int getIntZ() { return (int)(this->z); }
	POINT getPoint();

	// ======================= setter =======================
	void setX(float x) { this->x = x; }
	void setY(float y) { this->y = y; }
	void setZ(float z) { this->z = z; }

	// ======================= operator =======================
	vector3 operator+ (vector3& v);
	vector3 operator- (vector3& v);

	void operator+= (vector3& v);
	void operator-= (vector3& v);

	vector3 operator* (float& s);
	vector3 operator/ (float& s);

	bool operator== (vector3& v);
	bool operator!= (vector3& v);

	bool operator< (vector3& v);
	bool operator<=(vector3& v);

	// ======================= function =======================
	vector3 normalize(vector3 v);
	float toRadian(vector3 v);
	float length(vector3 v);
	float distance(vector3 vA, vector3 vB);
	float innerProduct(vector3 vA, vector3 vB);
	float externalProduct(vector3 vA, vector3 vB);

	// ======================= ���� ���� =======================
	float CounterClockWise(vector3 vA, vector3 vB); // �� ���� ���⼺�� Ȯ��
};
