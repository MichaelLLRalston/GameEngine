#pragma once
#include "Matrix3.h"
#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"

struct Matrix4
{
	Matrix4() {}
	union
	{
		float   v[16];
		float   m[4][4];
		Vector4 c[4];
	};

	Vector4  operator[](unsigned idx) const { return c[idx]; }
	Vector4 &operator[](unsigned idx) { return c[idx]; }

	Matrix4 transpose() const
	{
		Matrix4 r;
		r.c[0] = Vector4(m[0][0], m[1][0], m[2][0], m[3][0]);
		r.c[1] = Vector4(m[0][1], m[1][1], m[2][1], m[3][1]);
		r.c[2] = Vector4(m[0][2], m[1][2], m[2][2], m[3][2]);
		r.c[3] = Vector4(m[0][3], m[1][3], m[2][3], m[3][3]);
		return r;
	}

	float determinant();

	Matrix4 inverse();

	static Matrix4 identity()
	{
		Matrix4 r;
		r.c[0] = Vector4(1, 0, 0, 0);
		r.c[1] = Vector4(0, 1, 0, 0);
		r.c[2] = Vector4(0, 0, 1, 0);
		r.c[3] = Vector4(0, 0, 0, 1);
		return r;
	}

	// angle, in degrees
	static Matrix4 rotate(float angle)
	{
		Matrix4 r = identity();
		r.c[1] = Vector4(0, cosf(angle), sinf(angle), 0);
		r.c[2] = Vector4(0, -sinf(angle), cosf(angle), 0);
		return r;
	}

	static Matrix4 scale(const Vector3 &xy)
	{
		Matrix4 r = identity();
		r.m[0][0] = xy.x;
		r.m[1][1] = xy.y;
		r.m[2][2] = xy.z;
		return r;
	}

	static Matrix4 translate(const Vector3 &xy)
	{
		Matrix4 r = identity();
		r.m[2][0] = xy.x;
		r.m[2][1] = xy.y;
		r.m[2][2] = xy.z;
		return r;
	}
};


inline Matrix4 operator*(const Matrix4 &_A, const Matrix4 &B)
{
	//A can now access rows as Vector4
	Matrix4 r, A = _A.transpose();

	//for (size_t i = 0; i < 3; ++i)
	//    r.c[i] = Vector4(dot(A.c[0], B.c[i]), dot(A.c[1], B.c[i]), dot(A.c[2], B.c[i]));

	// Filling out columns for r here:
	r.c[0] = Vector4(dot(A.c[0], B.c[0]), dot(A.c[1], B.c[0]), dot(A.c[2], B.c[0]), dot(A.c[3], B.c[0]));
	r.c[1] = Vector4(dot(A.c[0], B.c[1]), dot(A.c[1], B.c[1]), dot(A.c[2], B.c[1]), dot(A.c[3], B.c[1]));
	r.c[2] = Vector4(dot(A.c[0], B.c[2]), dot(A.c[1], B.c[2]), dot(A.c[2], B.c[2]), dot(A.c[3], B.c[2]));
	r.c[3] = Vector4(dot(A.c[0], B.c[3]), dot(A.c[1], B.c[3]), dot(A.c[2], B.c[3]), dot(A.c[3], B.c[3]));
	return r;
}

inline Vector4 operator*(const Matrix4 &_A, const Vector4 &b)
{
	Matrix4 A = _A.transpose();
	Vector4 r;

	r.x = dot(A.c[0], b);
	r.y = dot(A.c[1], b);
	r.z = dot(A.c[2], b);
	r.q = dot(A.c[3], b);

	return r;
}