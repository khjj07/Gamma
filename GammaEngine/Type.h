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
};

struct rect2D {
	vector2 min;
	vector2 max;
};
