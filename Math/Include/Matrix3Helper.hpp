#pragma once

#ifndef _MATH_MATRIX3HELPER_
#define _MATH_MATRIX3HELPER_

#include "Matrix3.hpp"

namespace Fnd
{
namespace Math
{

/*
	An enum to describe the order of a 3x3 matrix.
	Used by matrix creation methods to create row or column major matrices.
*/
enum Matrix3_Order
{
	Matrix3_Row_Major = 0,
	Matrix3_Column_Major = 1
};


/*
	Templated helper class used to create 3x3 matrices.
	Template parameter specifies whether the methods should create a row or column major matrix.
*/
template <Matrix3_Order Order = Matrix3_Row_Major>
class Matrix3Helper
{
	public:

		// Create a rotation matrix describing a rotation around the X axis.
		// Takes the rotation in radians.
		inline static Matrix3 CreateXRotationMatrix( const float radians );

		// Create a rotation matrix describing a rotation around the Y axis.
		// Takes the rotation in radians.
		inline static Matrix3 CreateYRotationMatrix( const float radians );

		// Create a rotation matrix describing a rotation around the Z axis.
		// Takes the rotation in radians.
		inline static Matrix3 CreateZRotationMatrix( const float radians );

		// Create a uniform scale matrix.
		// Independent of matrix order.
		inline static Matrix3 CreateScaleMatrix( float scale );

		// Create a scale matrix.
		// Independent of matrix order.
		inline static Matrix3 CreateScaleMatrix( float scale_x, float scale_y, float scale_z );
};


/*
	Templated function used by the Matrix3Helper helper class to create row and column major matrices.
	Parameters are in row major order.
*/
template <Matrix3_Order Order>
inline Matrix3 CreateMatrix3(	float m00, float m01, float m02,
								float m10, float m11, float m12,
								float m20, float m21, float m22 );


/*
	--------------------------------
	Implementation.
*/


template <Matrix3_Order Order>
inline Matrix3 Matrix3Helper<Order>::CreateXRotationMatrix( const float radians )
{
	return CreateMatrix3<Order>( 	
		1.0f, 0.0f, 0.0f,
		0.0f, cos(radians), -sin(radians),
		0.0f, sin(radians), cos(radians) );
}

template <Matrix3_Order Order>
inline Matrix3 Matrix3Helper<Order>::CreateYRotationMatrix( const float radians )
{
	return CreateMatrix3<Order>(
		cos(radians), 0.0f, sin(radians),
		0.0f, 1.0f, 0.0f,
		-sin(radians), 0.0f, cos(radians) );
}

template <Matrix3_Order Order>
inline Matrix3 Matrix3Helper<Order>::CreateZRotationMatrix( const float radians )
{
	return CreateMatrix3<Order>(
		cos(radians), 0.0f, sin(radians),
		-sin(radians), 0.0f, cos(radians),
		0.0f, 1.0f, 0.0f );
}

template <Matrix3_Order Order>
inline Matrix3 Matrix3Helper<Order>::CreateScaleMatrix( float scale )
{
	return CreateMatrix3<Order>(
		scale, 0.0f, 0.0f,
		0.0f, scale, 0.0f,
		0.0f, 0.0f, scale );
}

template <Matrix3_Order Order>
inline Matrix3 Matrix3Helper<Order>::CreateScaleMatrix( float scale_x, float scale_y, float scale_z )
{
	return CreateMatrix3<Order>(
		scale_x, 0.0f, 0.0f,
		0.0f, scale_y, 0.0f,
		0.0f, 0.0f, scale_z );
}

// Specialised template function to create a row major matrix from row major parameters.
template <>
inline Matrix3 CreateMatrix3 <Matrix3_Row_Major>(	float m00, float m01, float m02,
													float m10, float m11, float m12,
													float m20, float m21, float m22 )
{
	return Matrix3(	m00, m01, m02,
					m10, m11, m12,
					m20, m21, m22 );
}

// Specialised template function to create a column major matrix from row major parameters.
template <>
inline Matrix3 CreateMatrix3 <Matrix3_Column_Major>(	float m00, float m01, float m02,
														float m10, float m11, float m12,
														float m20, float m21, float m22 )
{
	return Matrix3(	m00, m10, m20,
					m01, m11, m21,
					m02, m12, m22 );
}

}
}

#endif