#ifndef _VECTOR_2D_H_
#define _VECTOR_2D_H_

#include <cmath>
#include <cassert>

class CVector2D
{
public:
	float x, y;

	//构造
	CVector2D(float X = 0.0f, float Y = 0.0f)
		:
	x(X),y(Y)
	{}

	//长度
	float Length() const
	{
		return sqrt(x * x + y * y);
	}

	//单位向量
	CVector2D Normalize() const
	{
		float Len = Length();
		return CVector2D(x / Len, y / Len);
	}

	//加法
	CVector2D operator + (const CVector2D& that) const
	{
		return CVector2D(x + that.x, y + that.y);
	}

	//减法
	CVector2D operator - (const CVector2D& that) const
	{
		return CVector2D(x - that.x, y - that.y);
	}

	//数乘(向量*标量)
	CVector2D operator * (float f) const
	{
		return CVector2D(x * f, y * f);
	}

	//数除
	CVector2D operator / (float f) const
	{
		assert(f < -0.000001 || f > 0.000001);
		return CVector2D(x / f, y / f);
	}

	//点乘
	float operator * (const CVector2D& that) const
	{
		return x * that.x + y * that.y;
	}

	//投影(得到自己在that上的投影)
	CVector2D Shadow(const CVector2D& that) const
	{
		return that * ((*this * that) / (that.x * that.x + that.y * that.y));
	}
};

//数乘(标量*向量,是重载全局的*运算符)
inline CVector2D operator * (float f, const CVector2D& v)
{
	return CVector2D(f * v.x, f * v.y);
}

#endif