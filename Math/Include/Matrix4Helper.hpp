#pragma once

#ifndef _MATRIX4HELPER_
#define _MATRIX4HELPER_

#include "Matrix4.hpp"
#include "Vector3.hpp"
#include "Quaternion.hpp"

namespace Fnd
{
namespace Math
{

/*
	An enum to describe the order of a 3x3 matrix.
	Used by matrix creation methods to create row or column major matrices.
*/
enum Matrix4_Order
{
	Matrix4_Row_Major = 0,
	Matrix4_Column_Major = 1
};


/*
	Templated helper class used to create 4x4 matrices.
	Template parameter specifies whether the methods should create a row or column major matrix.
*/
template <Matrix4_Order Order = Matrix4_Row_Major>
class Matrix4Helper
{
	public:

		// Create a translation matrix from a vector.
		inline static Matrix4 CreateTranslationMatrix( const Vector3& vector );

		// Create a uniform scale matrix.
		// Independent of matrix order.
		inline static Matrix4 CreateScaleMatrix( const float s );

		// Create a scale matrix.
		// Independent of matrix order.
		inline static Matrix4 CreateScaleMatrix( const float x, const float y, const float z );

		// Create a rotation matrix describing a rotation around the X axis.
		// Takes the rotation in radians.
		inline static Matrix4 CreateXRotationMatrix( const float radians );

		// Create a rotation matrix describing a rotation around the Y axis.
		// Takes the rotation in radians.
		inline static Matrix4 CreateYRotationMatrix( const float radians );
		
		// Create a rotation matrix describing a rotation around the Z axis.
		// Takes the rotation in radians.
		inline static Matrix4 CreateZRotationMatrix( const float radians );

		// Create a rotation and translation matrix from a position and direction.
		// Create a 'world matrix' for a right handed coordinate system.
		inline static Matrix4 CreateWorldMatrixRH( const Vector3& position, const Vector3& direction, const Vector3& up = Vector3( 0.0f, 1.0f, 0.0f ) );

		// Create a rotation and translation matrix from a position and direction.
		// Creates a 'world matrix' for a left handed coordinate system.
		inline static Matrix4 CreateWorldMatrixLH( const Vector3& position, const Vector3& direction, const Vector3& up = Vector3( 0.0f, 1.0f, 0.0f ) );

		// Create a rotation and translation matrix from an 'eye' and a 'target'.
		// Creates a 'look at matrix' for a right handed coordinate system.
		inline static Matrix4 CreateLookAtMatrixRH( const Vector3& eye, const Vector3& target, const Vector3& up = Vector3( 0.0f, 1.0f, 0.0f ) );

		// Create a rotation and translation matrix from an 'eye' and a 'target'.
		// Creates a 'look at matrix' for a left handed coordinate system.
		inline static Matrix4 CreateLookAtMatrixLH( const Vector3& eye, const Vector3& target, const Vector3& up = Vector3( 0.0f, 1.0f, 0.0f ) );

		// Create a projection matrix from a field of view, aspect ratio and near and far planes.
		// Creates a projection matrix for a right handed coordinate system.
		inline static Matrix4 CreateProjectionMatrixRH( const float fov_rad, const float aspect, const float near_plane, const float far_plane );

		// Create a projection matrix from a field of view, aspect ratio and near and far planes.
		// Creates a projection matrix for a left handed coordinate system.
		inline static Matrix4 CreateProjectionMatrixLH( const float fov_rad, const float aspect, const float near_plane, const float far_plane );

		// Transforms a 3d position by a 4x4 matrix.
		inline static Vector3 TransformPosition( const Vector3& vector, const Matrix4& matrix );

		// Transforms a 3d direction by a 4x4 matrix.
		inline static Vector3 TransformDirection( const Vector3& vector, const Matrix4& matrix );

		inline static Matrix4 CreateRotationMatrix( const Quaternion& quaternion );
};

/*
	Templated function used by the Matrix4Helper helper class to create row and column major matrices.
	Parameters are in row major order.
*/
template <Matrix4_Order Order>
inline Matrix4 CreateMatrix4(	float m00, float m01, float m02, float m03,
								float m10, float m11, float m12, float m13,
								float m20, float m21, float m22, float m23,
								float m30, float m31, float m32, float m33 );


/*
	--------------------------------
	Implementation.
*/


template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateTranslationMatrix( const Vector3& vector )
{
	return CreateMatrix4<Order>(	
							1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							vector.x, vector.y, vector.z, 1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateScaleMatrix( const float s )
{
	return Matrix4( 	s, 0.0f, 0.0f, 0.0f,
						0.0f, s, 0.0f, 0.0f,
						0.0f, 0.0f, s, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateScaleMatrix( const float x, const float y, const float z )
{
	return Matrix4( 	x, 0.0f, 0.0f, 0.0f,
						0.0f, y, 0.0f, 0.0f,
						0.0f, 0.0f, z, 0.0f,
						0.0f, 0.0f, 0.0f, 1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateXRotationMatrix( const float radians )
{
	return CreateMatrix4<Order>( 	
							1.0f, 0.0f, 0.0f, 0.0f,
							0.0f, cos(radians), -sin(radians), 0.0f,
							0.0f, sin(radians), cos(radians), 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateYRotationMatrix( const float radians )
{
	return CreateMatrix4<Order>( 	
							cos(radians), 0.0f, sin(radians), 0.0f,
							0.0f, 1.0f, 0.0f, 0.0f,
							-sin(radians), 0.0f, cos(radians), 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateZRotationMatrix( const float radians )
{
	return CreateMatrix4<Order>( 	
							cos(radians), -sin(radians), 0.0f, 0.0f,
							sin(radians), cos(radians), 0.0f, 0.0f,
							0.0f, 0.0f, 1.0f, 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateWorldMatrixRH( const Vector3& position, const Vector3& direction, const Vector3& up )
{
    const Vector3 z_axis( -normalise( direction ) );
    const Vector3 x_axis( normalise( cross( up, z_axis ) ) );
    const Vector3 y_axis( cross( z_axis, x_axis ) );
    return CreateMatrix4<Order>(	
					x_axis.x, x_axis.y, x_axis.z, 0.0f,
                    y_axis.x, y_axis.y, y_axis.z, 0.0f,
                    z_axis.x, z_axis.y, z_axis.z, 0.0f,
                    position.x, position.y, position.z, 1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateWorldMatrixLH( const Vector3& position, const Vector3& direction, const Vector3& up )
{
    const Vector3 z_axis( normalise( direction ) );
    const Vector3 x_axis( normalise( cross( up, z_axis ) ) );
    const Vector3 y_axis( cross( z_axis, x_axis ) );
    return CreateMatrix4<Order>(
					x_axis.x, x_axis.y, x_axis.z, 0.0f,
                    y_axis.x, y_axis.y, y_axis.z, 0.0f,
                    z_axis.x, z_axis.y, z_axis.z, 0.0f,
                    position.x, position.y, position.z, 1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateLookAtMatrixRH( const Vector3& eye, const Vector3& target, const Vector3& up )
{
	const Vector3 z_axis( normalise( eye - target ) );
	const Vector3 x_axis( normalise( cross( up, z_axis ) ) );
	const Vector3 y_axis( normalise( cross( z_axis, x_axis ) ) );
	return CreateMatrix4<Order>(	
					x_axis.x, y_axis.x, z_axis.x, 0.0f,
					x_axis.y, y_axis.y, z_axis.y, 0.0f,
					x_axis.z, y_axis.z, z_axis.z, 0.0f,
					dot( x_axis, eye ),	dot( y_axis, eye ),	dot( z_axis, eye ),	1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateLookAtMatrixLH( const Vector3& eye, const Vector3& target, const Vector3& up )
{
	const Vector3 z_axis( normalise( target - eye ) );
	const Vector3 x_axis( normalise( cross( up, z_axis ) ) );
	const Vector3 y_axis( normalise( cross( z_axis, x_axis ) ) );
	return CreateMatrix4<Order>(	
					x_axis.x,	y_axis.x,	z_axis.x,	0.0f,
					x_axis.y,	y_axis.y,	z_axis.y,	0.0f,
					x_axis.z,	y_axis.z,	z_axis.z,	0.0f,
					-dot( x_axis, eye ),	-dot( y_axis, eye ),	-dot( z_axis, eye ),	1.0f );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateProjectionMatrixRH( const float fov_rad, const float aspect, const float near_plane, const float far_plane )
{
	const float y_scale = 1.0f / tan( fov_rad / 2.0f );
	return CreateMatrix4<Order>(	
					y_scale / aspect, 0.0f, 0.0f, 0.0f,
					0.0f, y_scale, 0.0f, 0.0f, 
					0.0f, 0.0f, far_plane / ( near_plane - far_plane ), -1.0f,
					0, 0, near_plane * far_plane / ( near_plane - far_plane ), 0 );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateProjectionMatrixLH( const float fov_rad, const float aspect, const float near_plane, const float far_plane )
{
	const float y_scale = 1.0f / tan( fov_rad / 2.0f );
	return CreateMatrix4<Order>(	
					y_scale / aspect, 0.0f, 0.0f, 0.0f,
					0.0f, y_scale, 0.0f, 0.0f,
					0.0f, 0.0f, far_plane / ( far_plane - near_plane ), 1.f,
					0.0f, 0.0f, -near_plane * far_plane / ( far_plane - near_plane ), 0.0f );
}

template <Matrix4_Order Order>
inline Vector3 Matrix4Helper<Order>::TransformPosition( const Vector3& vector, const Matrix4& matrix)
{
    const Vector4 hvector =	Order == Matrix4_Row_Major ?
							Vector4( vector.x, vector.y, vector.z, 1.0f ) * matrix :
							matrix * Vector4( vector.x, vector.y, vector.z, 1.0f );

    return Vector3( hvector.x, hvector.y, hvector.z ) / hvector.w;
}

template <Matrix4_Order Order>
inline Vector3 Matrix4Helper<Order>::TransformDirection( const Vector3& vector, const Matrix4& matrix )
{
    const Vector4 hvector =	Order == Matrix4_Row_Major ?
							Vector4( vector.x, vector.y, vector.z, 0.0f ) * matrix :
							matrix * Vector4( vector.x, vector.y, vector.z, 0.0f );

    return Vector3( hvector.x, hvector.y, hvector.z );
}

// Specialised template function to create a row major matrix from row major parameters.
template <>
inline Matrix4 CreateMatrix4 <Matrix4_Row_Major>(	
								float m00, float m01, float m02, float m03,
								float m10, float m11, float m12, float m13,
								float m20, float m21, float m22, float m23,
								float m30, float m31, float m32, float m33 )
{
	return Matrix4(	m00, m01, m02, m03,
					m10, m11, m12, m13,
					m20, m21, m22, m23,
					m30, m31, m32, m33 );
}

// Specialised template function to create a column major matrix from row major parameters.
template <>
inline Matrix4 CreateMatrix4 <Matrix4_Column_Major>(	
								float m00, float m01, float m02, float m03,
								float m10, float m11, float m12, float m13,
								float m20, float m21, float m22, float m23,
								float m30, float m31, float m32, float m33 )
{
	return Matrix4(	m00, m10, m20, m30,
					m01, m11, m12, m13,
					m02, m12, m22, m32,
					m03, m13, m23, m33 );
}

template <Matrix4_Order Order>
inline Matrix4 Matrix4Helper<Order>::CreateRotationMatrix( const Quaternion& q )
{
	/*const float x = q.x;
	const float y = q.y;
	const float z = q.z;
	const float w = q.w;

	const float x2 = x*x;
	const float y2 = y*y;
	const float z2 = z*z;
	const float w2 = w*w;

	return CreateMatrix4<Order>( 
		w2 + x2 - y2 - z2, 2*x*y - 2*w*z, 2*x*z + 2*w*y, 0,
		2*x*y + 2*w*z, w2 - x2 + y2 - z2, 2*y*z + 2*w*x, 0,
		2*x*z - 2*w*y, 2*y*z - 2*w*x, w2 - x2 - y2 + z2, 0,
		0, 0, 0, 1 );
	*/

	const Vector3 x = normalise( q.GetXAxis() );
	const Vector3 y = normalise( q.GetYAxis() );
	const Vector3 z = normalise( cross( x, y ) );

	return CreateMatrix4<Order>(
		x.x, x.y, x.z, 0,
		y.x, y.y, y.z, 0,
		z.x, z.y, z.z, 0,
		0, 0, 0, 1 );

}

}
}

#endif