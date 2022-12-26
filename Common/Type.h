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

/// <summary>
/// 2방향 벡터 자료형
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
		vector2 result = vector2(x / this->Length(), y / this->Length());
		return result;
	}

	static vector2 Normalize(vector2 v)
	{
		vector2 result = vector2( v.x / Length(v),v.y / Length(v) );
		return result;
	}

	static vector2 Reflect(vector2 v,vector2 normal)
	{
		return v - normal * vector2::Dot(v, normal) * 2;
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

