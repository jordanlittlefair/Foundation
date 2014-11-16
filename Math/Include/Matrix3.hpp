#pragma once

#ifndef _MATRIX3_
#define _MATRIX3_

#include "Vector3.hpp"

namespace Fnd
{
namespace Math
{

/*
	3x3 Matrix.
*/
struct Matrix3
{
	float m00;
	float m01;
	float m02;

	float m10;
	float m11;
	float m12;

	float m20;
	float m21;
	float m22;

	inline Matrix3();

	inline Matrix3(	const float i00, const float i01, const float i02,
					const float i10, const float i11, const float i12,
					const float i20, const float i21, const float i22 );

	inline static Matrix3 Identity();
	
	// Get the transpose of the matrix.
	// Independent of matrix order.
	inline static Matrix3 Transpose( const Matrix3& m );

	// Get the inverse of the matrix.
	// Independent of the matrix order?
	inline static Matrix3 Inverse( const Matrix3& m );
};


/*
	Operators.
*/

inline Matrix3 operator *( const Matrix3& m1, const Matrix3& m2 );
inline Vector3 operator *( const Vector3& v, const Matrix3& m );
inline Vector3 operator *( const Matrix3& m, const Vector3& v );


/*
	--------------------------------
	Implementation.
*/

inline Matrix3::Matrix3()
{
}

inline Matrix3::Matrix3(	float i00, float i01, float i02,
					float i10, float i11, float i12,
					float i20, float i21, float i22 ): 
	m00(i00), m01(i01), m02(i02),
	m10(i10), m11(i11), m12(i12),
	m20(i20), m21(i21), m22(i22)
{
}

inline Matrix3 Matrix3::Identity()
{
	return Matrix3(	1.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 1.0f );
}

inline Matrix3 Matrix3::Transpose( const Matrix3& m )
{
	return Matrix3(	m.m00,	m.m10,	m.m20,
					m.m01,	m.m11,	m.m21,
					m.m02,	m.m12,	m.m22 );
}

inline Matrix3 Matrix3::Inverse( const Matrix3& m )
{
	Matrix3 to_return(

		m.m11 * m.m22 - m.m12 * m.m21,
		m.m02 * m.m21 - m.m01 * m.m22,
		m.m01 * m.m12 - m.m02 * m.m11,

		m.m12 * m.m20 - m.m10 * m.m22,
		m.m00 * m.m22 - m.m02 * m.m20,
		m.m02 * m.m10 - m.m00 * m.m12,

		m.m10 * m.m21 - m.m11 * m.m20,
		m.m01 * m.m20 - m.m00 * m.m21,
		m.m00 * m.m11 - m.m01 * m.m10
	);

	const float determinant =
		to_return.m00 * m.m00 +
		to_return.m10 * m.m01 +
		to_return.m20 * m.m02;

	for ( unsigned int i = 0; i < 9; ++i )
	{
		((float*)&to_return)[i] /= determinant;
	}

	return to_return;
}

inline Matrix3 operator *( const Matrix3& m1, const Matrix3& m2 )
{
	return Matrix3(	m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20,
					m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21,
					m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22,
					m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20,
					m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21,
					m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22,
					m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20,
					m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21,
					m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22 );
}

inline Vector3 operator *( const Vector3& v, const Matrix3& m )
{
    return Vector3( v.x * m.m00 + v.y * m.m10 + v.z * m.m20,
                    v.x * m.m01 + v.y * m.m11 + v.z * m.m21,
                    v.x * m.m02 + v.y * m.m12 + v.z * m.m22 );
}

inline Vector3 operator *( const Matrix3& m, const Vector3& v )
{
    return Vector3( v.x * m.m00 + v.y * m.m01 + v.z * m.m02,
                    v.x * m.m10 + v.y * m.m11 + v.z * m.m12,
                    v.x * m.m20 + v.y * m.m21 + v.z * m.m22 );
}

}
}

#endif