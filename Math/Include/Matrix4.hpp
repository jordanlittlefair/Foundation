#pragma once

#ifndef _MATRIX4_
#define _MATRIX4_

#include "Vector4.hpp"

namespace Fnd
{
namespace Math
{

/*
	4x4 Matrix.
*/
struct Matrix4
{
	float m00;
	float m01;
	float m02;
	float m03;

	float m10;
	float m11;
	float m12;
	float m13;

	float m20;
	float m21;
	float m22;
	float m23;

	float m30;
	float m31;
	float m32;
	float m33;

	inline Matrix4();

	inline Matrix4(	const float i00, const float i01, const float i02, const float i03,
					const float i10, const float i11, const float i12, const float i13,
					const float i20, const float i21, const float i22, const float i23,
					const float i30, const float i31, const float i32, const float i33 );

	inline static Matrix4 Identity();
	
	// Get the transpose of the matrix.
	// Independent of matrix order.
	inline static Matrix4 Transpose( const Matrix4& m );

	// Get the inverse of the matrix.
	// Independent of the matrix order?
	inline static Matrix4 Inverse( const Matrix4& m );
};


/*
	Operators.
*/

inline Matrix4 operator *( const Matrix4& m1, const Matrix4& m2 );
inline Vector4 operator *( const Vector4& v, const Matrix4& m );
inline Vector4 operator *( const Matrix4& m, const Vector4& v );


/*
	--------------------------------
	Implementation.
*/

#include "MathUtility.hpp"

inline Matrix4::Matrix4()
{
}

inline Matrix4::Matrix4( float i00, float i01, float i02, float i03,
				float i10, float i11, float i12, float i13,
				float i20, float i21, float i22, float i23,
				float i30, float i31, float i32, float i33 ): 
	m00(i00), m01(i01), m02(i02), m03(i03),
	m10(i10), m11(i11), m12(i12), m13(i13),
	m20(i20), m21(i21), m22(i22), m23(i23),
	m30(i30), m31(i31), m32(i32), m33(i33)
{
}

inline Matrix4 Matrix4::Identity()
{
	return Matrix4(	1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f );
}

inline Matrix4 Matrix4::Transpose( const Matrix4& m )
{
	return Matrix4(	m.m00,	m.m10,	m.m20,	m.m30,
					m.m01,	m.m11,	m.m21,	m.m31,
					m.m02,	m.m12,	m.m22,	m.m32,
					m.m03,	m.m13,	m.m23,	m.m33 );
}

inline Matrix4 Matrix4::Inverse( const Matrix4& m )
{
	float v0 = m.m20 * m.m31 - m.m21 * m.m30;
	float v1 = m.m20 * m.m32 - m.m22 * m.m30;
	float v2 = m.m20 * m.m33 - m.m23 * m.m30;
	float v3 = m.m21 * m.m32 - m.m22 * m.m31;
	float v4 = m.m21 * m.m33 - m.m23 * m.m31;
	float v5 = m.m22 * m.m33 - m.m23 * m.m32;

	const float t00 = + (v5 * m.m11 - v4 * m.m12 + v3 * m.m13);
	const float t10 = - (v5 * m.m10 - v2 * m.m12 + v1 * m.m13);
	const float t20 = + (v4 * m.m10 - v2 * m.m11 + v0 * m.m13);
	const float t30 = - (v3 * m.m10 - v1 * m.m11 + v0 * m.m12);

	const float determinant = t00 * m.m00 + t10 * m.m01 + t20 * m.m02 + t30 * m.m03;

	const float d00 = t00 / determinant;
 	const float d10 = t10 / determinant;
 	const float d20 = t20 / determinant;
	const float d30 = t30 / determinant;

	const float d01 = - (v5 * m.m01 - v4 * m.m02 + v3 * m.m03) / determinant;
	const float d11 = + (v5 * m.m00 - v2 * m.m02 + v1 * m.m03) / determinant;
	const float d21 = - (v4 * m.m00 - v2 * m.m01 + v0 * m.m03) / determinant;
	const float d31 = + (v3 * m.m00 - v1 * m.m01 + v0 * m.m02) / determinant;

	v0 = m.m10 * m.m31 - m.m11 * m.m30;
	v1 = m.m10 * m.m32 - m.m12 * m.m30;
	v2 = m.m10 * m.m33 - m.m13 * m.m30;
	v3 = m.m11 * m.m32 - m.m12 * m.m31;
	v4 = m.m11 * m.m33 - m.m13 * m.m31;
	v5 = m.m12 * m.m33 - m.m13 * m.m32;
	
	const float d02 = + (v5 * m.m01 - v4 * m.m02 + v3 * m.m03) / determinant;
	const float d12 = - (v5 * m.m00 - v2 * m.m02 + v1 * m.m03) / determinant;
	const float d22 = + (v4 * m.m00 - v2 * m.m01 + v0 * m.m03) / determinant;
	const float d32 = - (v3 * m.m00 - v1 * m.m01 + v0 * m.m02) / determinant;

	v0 = m.m21 * m.m10 - m.m20 * m.m11;
	v1 = m.m22 * m.m10 - m.m20 * m.m12;
	v2 = m.m23 * m.m10 - m.m20 * m.m13;
	v3 = m.m22 * m.m11 - m.m21 * m.m12;
	v4 = m.m23 * m.m11 - m.m21 * m.m13;
	v5 = m.m23 * m.m12 - m.m22 * m.m13;

	const float d03 = - (v5 * m.m01 - v4 * m.m02 + v3 * m.m03) / determinant;
	const float d13 = + (v5 * m.m00 - v2 * m.m02 + v1 * m.m03) / determinant;
	const float d23 = - (v4 * m.m00 - v2 * m.m01 + v0 * m.m03) / determinant;
	const float d33 = + (v3 * m.m00 - v1 * m.m01 + v0 * m.m02) / determinant;

	return Matrix4(
		d00, d01, d02, d03,
		d10, d11, d12, d13,
		d20, d21, d22, d23,
		d30, d31, d32, d33 );
}

inline Matrix4 operator *( const Matrix4& m1, const Matrix4& m2 )
{
	return Matrix4(	m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20 + m1.m03 * m2.m30,
					m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21 + m1.m03 * m2.m31,
					m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22 + m1.m03 * m2.m32,
					m1.m00 * m2.m03 + m1.m01 * m2.m13 + m1.m02 * m2.m23 + m1.m03 * m2.m33,
					m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20 + m1.m13 * m2.m30,
					m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31,
					m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32,
					m1.m10 * m2.m03 + m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33,
					m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20 + m1.m23 * m2.m30,
					m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31,
					m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32,
					m1.m20 * m2.m03 + m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33,
					m1.m30 * m2.m00 + m1.m31 * m2.m10 + m1.m32 * m2.m20 + m1.m33 * m2.m30,
					m1.m30 * m2.m01 + m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31,
					m1.m30 * m2.m02 + m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32,
					m1.m30 * m2.m03 + m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33 );
}

inline Vector4 operator *( const Vector4& v, const Matrix4& m )
{
	return Vector4( v.x * m.m00 + v.y * m.m10 + v.z * m.m20 + v.w * m.m30,
                    v.x * m.m01 + v.y * m.m11 + v.z * m.m21 + v.w * m.m31,
                    v.x * m.m02 + v.y * m.m12 + v.z * m.m22 + v.w * m.m32,
                    v.x * m.m03 + v.y * m.m13 + v.z * m.m23 + v.w * m.m33 );
}

inline Vector4 operator *( const Matrix4& m, const Vector4& v )
{    
	return Vector4( v.x * m.m00 + v.y * m.m01 + v.z * m.m02 + v.w * m.m03,
                    v.x * m.m10 + v.y * m.m11 + v.z * m.m12 + v.w * m.m13,
                    v.x * m.m20 + v.y * m.m21 + v.z * m.m22 + v.w * m.m23,
                    v.x * m.m30 + v.y * m.m31 + v.z * m.m32 + v.w * m.m33 );
}

}
}

#endif