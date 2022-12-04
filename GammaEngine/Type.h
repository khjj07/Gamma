#pragma once
struct vector2
{
	float x;
	float y;
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
	vector2 operator +(vector2 a)
	{
		return vector2(x + a.x, y + a.y);
	}
	vector2 operator -(vector2 a)
	{
		return vector2(x - a.x, y - a.y);
	}
	vector2 operator *(float a)
	{
		return vector2(x*a, y*a);
	}
	vector2 operator /(float a)
	{
		return vector2(x / a, y / a);
	}


	vector2& operator +=(vector2& a)
	{
		(*this) = (*this) + a;
		return *this;
	}
	vector2& operator -=(vector2& a)
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

struct rect2D {
	vector2 min;
	vector2 max;
};


