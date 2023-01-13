#pragma once
struct  vector2;

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
	vector2 tovector2();
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
	vector2 tovector2();
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

	static Matrix3x3 Scale(float p_xRatio, float p_yRatio)
	{
		Matrix3x3 result(
			p_xRatio, 0.f, 0.f,
			0.f, p_yRatio, 0.f,
			0.f, 0.f, 1.f
		);

		return result;
	}

	vector2 tovector2();
};

Matrix3x3 operator*(Matrix3x3 a, Matrix3x3 b);

Matrix1x3 operator*(Matrix1x3 a, Matrix3x3 b);


Matrix3x1 operator*(Matrix3x3 a, Matrix3x1 b);
