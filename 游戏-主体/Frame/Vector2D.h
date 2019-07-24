#ifndef _VECTOR_2D_H_
#define _VECTOR_2D_H_

#include <cmath>
#include <cassert>

class CVector2D
{
public:
	float x, y;

	//����
	CVector2D(float X = 0.0f, float Y = 0.0f)
		:
	x(X),y(Y)
	{}

	//����
	float Length() const
	{
		return sqrt(x * x + y * y);
	}

	//��λ����
	CVector2D Normalize() const
	{
		float Len = Length();
		return CVector2D(x / Len, y / Len);
	}

	//�ӷ�
	CVector2D operator + (const CVector2D& that) const
	{
		return CVector2D(x + that.x, y + that.y);
	}

	//����
	CVector2D operator - (const CVector2D& that) const
	{
		return CVector2D(x - that.x, y - that.y);
	}

	//����(����*����)
	CVector2D operator * (float f) const
	{
		return CVector2D(x * f, y * f);
	}

	//����
	CVector2D operator / (float f) const
	{
		assert(f < -0.000001 || f > 0.000001);
		return CVector2D(x / f, y / f);
	}

	//���
	float operator * (const CVector2D& that) const
	{
		return x * that.x + y * that.y;
	}

	//ͶӰ(�õ��Լ���that�ϵ�ͶӰ)
	CVector2D Shadow(const CVector2D& that) const
	{
		return that * ((*this * that) / (that.x * that.x + that.y * that.y));
	}
};

//����(����*����,������ȫ�ֵ�*�����)
inline CVector2D operator * (float f, const CVector2D& v)
{
	return CVector2D(f * v.x, f * v.y);
}

#endif