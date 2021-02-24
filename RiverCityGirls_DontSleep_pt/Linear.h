#pragma once

/*====================================================================
							1�� ���� ��ƿ
====================================================================*/
enum class LINEAR_TYPE
{
	ON,		//���п� �پ� ����
	UP,		//������ ���� ����
	DOWN,	//������ �Ʒ��� ����
	RIGHT,	//������ ���ʿ� ����
	LEFT,	//������ �����ʿ� ����
};

//1�� �Լ�, ������ �������� ��� ��ġ�ϴ��� �Ǵ�
class Linear
{
	float a;	//x ����
	float b;	//y ����

	vector3 vStart;
	vector3 vEnd;

public:
	Linear() {}
	Linear(float a, float b, vector3 start, vector3 end) :a(a), b(b), vStart(start), vEnd(end) {} // ����, ����, ������, ������ ��� ������ ���� �����
	Linear(vector3 start, vector3 end);
	
/*====================================================================
								GETTER
====================================================================*/
	//getter
	LINEAR_TYPE getType(float x, float y);
	float getX(float y) { return (y - b) / a; }
	float getY(float x) { return a * x + b; }
	vector3 getStart() { return vStart; }
	vector3 getEnd() { return vEnd; }
	float geta() { return a; }
	float getb() { return b; }

/*====================================================================
								FUNCTION
====================================================================*/
	// ������ ���ϴ� ������
	Linear linearFromPoints(vector3 start, vector3 end);

	// ������ ������ Ȯ���ϰ� �������� *vP�� ����ش�*
	// ĳ���� �������� ȣ��, lB���� ������Ʈ�� ������ �־��ش�. (������ �� ���Ѿ� �Ѵ�!)
	bool segmentIntersect(Linear lB, vector3* vP);

	//���� �׸���
	void LinearRender(HDC hdc);

};

