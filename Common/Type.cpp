#include <math.h>
#include "type.h"

const vector2 vector2::Zero = vector2(0, 0);
const vector2 vector2::Up = vector2(0, -1);
const vector2 vector2::Down = vector2(0, 1);
const vector2 vector2::Left = vector2(-1, 0);
const vector2 vector2::Right = vector2(1, 0);
const Matrix3x3 Matrix3x3::Identity = Matrix3x3(1,0,0,0,1,0,0,0,1);


Matrix3x3 operator*(Matrix3x3 a, Matrix3x3 b)
{
	Matrix3x3 result;
	result[0][0] = a[0][0] * b[0][0] + a[0][1] * b[1][0] + a[0][2] * b[2][0];
	result[0][1] = a[0][0] * b[0][1] + a[0][1] * b[1][1] + a[0][2] * b[2][1];
	result[0][2] = a[0][0] * b[0][2] + a[0][1] * b[1][2] + a[0][2] * b[2][2];

	result[1][0] = a[1][0] * b[0][0] + a[1][1] * b[1][0] + a[1][2] * b[2][0];
	result[1][1] = a[1][0] * b[0][1] + a[1][1] * b[1][1] + a[1][2] * b[2][1];
	result[1][2] = a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2];

	result[2][0] = a[2][0] * b[0][0] + a[2][1] * b[1][0] + a[2][2] * b[2][0];
	result[2][1] = a[2][0] * b[0][1] + a[2][1] * b[1][1] + a[2][2] * b[2][1];
	result[2][2] = a[2][0] * b[0][2] + a[2][1] * b[1][2] + a[2][2] * b[2][2];
	return result;
}

Matrix1x3 operator*(Matrix1x3 a, Matrix3x3 b)
{
	Matrix1x3 result;
	result[0] = a[0] * b[0][0] + a[1] * b[1][0] + a[2] * b[2][0];
	result[1] = a[1] * b[0][1] + a[1] * b[1][1] + a[2] * b[2][1];
	result[2] = a[2] * b[0][2] + a[1] * b[1][2] + a[2] * b[2][2];
	return result;
}

Matrix3x1 operator*(Matrix3x3 a, Matrix3x1 b)
{
	Matrix3x1 result;
	result[0] = a[0][0] * b[0] + a[0][1] * b[1] + a[0][2] * b[2];
	result[1] = a[1][0] * b[0] + a[1][1] * b[1] + a[1][2] * b[2];
	result[2] = a[2][0] * b[0] + a[2][1] * b[1] + a[2][2] * b[2];
	return result;
}