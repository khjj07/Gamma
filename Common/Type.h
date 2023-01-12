#pragma once
#include <cmath>
#include <xhash>

/// <summary>
/// Tween의 재생 정보를 표현하는 enum 타입 
/// </summary>
enum PLAYBACK
{
	ONCE_FORWARD,//1회 정방향
	ONCE_BACKWARD,//1회 역방향
	ONCE_PINGPONG,//1회 왔다갔다
	LOOP_FORWARD,//반복 정방향
	LOOP_BACKWARD,//반복 역방향
	LOOP_PINGPONG//반복 왔다갔다
};

struct Matrix3x1
{
	float value[3];
	float& operator[](int i)
	{
		return value[i];
	};
	Matrix3x1()
	{
		value[0] = 0;
		value[1] = 0;
		value[2] = 0;
	}
	Matrix3x1(float a0, float a1, float a2)
	{
		value[0] = a0;
		value[1] = a1;
		value[2] = a2;
	}


};



struct Matrix1x3
{
	float value[3];
	float& operator[](int i)
	{
		return value[i];
	};
	Matrix1x3()
	{
		value[0] = 0;
		value[1] = 0;
		value[2] = 0;
	}
	Matrix1x3(float a0, float a1, float a2)
	{
		value[0] = a0;
		value[1] = a1;
		value[2] = a2;
	}
};

struct Matrix3x3
{
	Matrix3x1 value[3];
	Matrix3x3()
	{
		value[0][0] = 0;
		value[0][1] = 0;
		value[0][2] = 0;
		value[1][0] = 0;
		value[1][1] = 0;
		value[1][2] = 0;
		value[2][0] = 0;
		value[2][1] = 0;
		value[2][2] = 0;
	}

	Matrix3x3(float a0, float a1, float a2, float b0, float b1, float b2, float c0, float c1, float c2)
	{
		value[0][0] = a0;
		value[0][1] = a1;
		value[0][2] = a2;
		value[1][0] = b0;
		value[1][1] = b1;
		value[1][2] = b2;
		value[2][0] = c0;
		value[2][1] = c1;
		value[2][2] = c2;
	}

	Matrix3x1& operator[](int i)
	{
		return value[i];
	};
	const static Matrix3x3 Identity;

	static Matrix3x3 Translation(float p_xPos, float p_yPos)
	{
		Matrix3x3 result(
			1.f, 0.f, p_xPos,
			0.f, 1.f, p_yPos,
			0.f, 0.f, 1.f
		);

		return result;
	}

	// 회전 행렬을 반환하는 함수
	static Matrix3x3 Rotate(float p_euler)
	{
		double rad = p_euler * (3.141592 / 180.f);

		Matrix3x3 result(
			cos(rad), sin(rad), 0.f,
			-sin(rad), cos(rad), 0.f,
			0.f, 0.f, 1.f
		);

		return result;
	}

	// 크기 행렬을 반환하는 함수
	static Matrix3x3 Scale(float p_xRatio, float p_yRatio)
	{
		Matrix3x3 result(
			p_xRatio, 0.f, 0.f,
			0.f, p_yRatio, 0.f,
			0.f, 0.f, 1.f
		);

		return result;
	}
};

Matrix3x3 operator*(Matrix3x3 a, Matrix3x3 b);

Matrix1x3 operator*(Matrix1x3 a, Matrix3x3 b);


Matrix3x1 operator*(Matrix3x3 a, Matrix3x1 b);

/// <summary>
/// 2차원 벡터 자료형
/// </summary>
struct vector2
{
	float x;
	float y;
	const static vector2 Zero;
	const static vector2 Up;
	const static vector2 Down;
	const static vector2 Left;
	const static vector2 Right;
	
	vector2()
	{
		x = 0;
		y = 0;
	}

	vector2(float a,float b)
	{
		x = a;
		y = b;
	}

	friend bool operator ==(vector2 a, vector2 b)
	{
		return a.x == b.x && a.y == b.y;
	}

	friend bool operator !=(vector2& a, vector2& b)
	{
		return a.x != b.x || a.y != b.y;
	}

	vector2 operator -()
	{
		return vector2(-x, -y);
	}

	vector2 operator +(vector2 a) const
	{
		return vector2(x + a.x, y + a.y);
	}

	vector2 operator -(vector2 a) const
	{
		return vector2(x - a.x, y - a.y);
	}

	vector2 operator *(float a) const
	{
		return vector2(x*a, y*a);
	}

	vector2 operator /(float a) const
	{
		return vector2(x / a, y / a);
	}

	vector2& operator +=(vector2& a)
	{
		(*this) = (*this) + a;
		return *this;
	}

	vector2& operator +=(vector2 a)
	{
		(*this) = (*this) + a;
		return *this;
	}

	vector2& operator -=(vector2& a)
	{
		(*this) = (*this) - a;
		return *this;
	}

	vector2& operator -=(vector2 a)
	{
		(*this) = (*this) - a;
		return *this;
	}

	static float Dot(vector2 v1, vector2 v2)
	{
		float result = v1.x * v2.x + v1.y * v2.y;
		return result;
	}

	static vector2 TripleProduct(vector2 a, vector2 b, vector2 c)
	{
		return -a * (vector2::Dot(b, c)) + b * (vector2::Dot(a, c));
	}

	float Length()
	{
		return (float)(pow(x * x + y * y, 0.5));
	}

	static float Length(vector2 v)
	{
		return (float)(pow(v.x * v.x + v.y * v.y, 0.5));
	}

	static float Distance(vector2 v1, vector2 v2)
	{
		float result = (float)pow((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y), 0.5);
		return result;
	}

	vector2 Normalize()
	{
		if (Length() == 0)
		{
			return vector2();
		}
		vector2 result = vector2(x / this->Length(), y / this->Length());
		return result;
	}

	static vector2 Normalize(vector2 v)
	{
		if (Length(v)==0)
		{
			return vector2();
		}
		vector2 result = vector2( v.x / Length(v),v.y / Length(v) );
		return result;
	}

	static vector2 Reflect(vector2 v,vector2 normal)
	{
		return v - normal * vector2::Dot(v, normal) * 2;
	}
	
	Matrix3x1 ToMatrix3x1()
	{
		Matrix3x1 result;
		result[0] = x;
		result[1] = y;
		return result;
	}

	Matrix1x3 ToMatrix1x3()
	{
		Matrix1x3 result;
		result[0] = x;
		result[1] = y;
		return result;
	}
};

struct vector4
{
	float x;
	float y;
	float z;
	float w;

	vector4()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	vector4(float a, float b,float c,float d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}

	bool operator == (const vector4& other) const {
		if (x == other.x && y == other.y && z==other.z && w==other.w)
			return true;
		return false;
	}
};

namespace std {
	template <>
	struct hash<vector4> {
		size_t operator()(const vector4& vec) const {
			hash<float> hash_func; 
			return hash_func(vec.x + vec.y*10 + vec.w*100 + vec.z*1000);
		}
	};
}

struct rect2D {
	vector2 min;
	vector2 max;
};
