#pragma once

#ifndef _VECTOR3_
#define _VECTOR3_

#include "MathUtility.hpp"

namespace Fnd
{
namespace Math
{

/*
	3D Vector.
*/
struct Vector3
{
    float x;
    float y;
    float z;

    inline Vector3();
    inline Vector3( const float X, const float Y, const float Z );
	inline Vector3& operator =( const Vector3& v );

	inline static Vector3 Zero();
	inline static Vector3 RandomUnit();
	inline static Vector3 RandomDirection( const Vector3& direction, float angle_variation );
};


/*
	Operators.
*/

inline Vector3 operator +( const Vector3& v );
inline Vector3 operator -( const Vector3& v );
inline Vector3 operator +( const Vector3& v1, const Vector3& v2 );
inline Vector3 operator -( const Vector3& v1, const Vector3& v2 );
inline Vector3 operator *( const float f, const Vector3& v );
inline Vector3 operator *( const Vector3& v, const float f );
inline Vector3 operator *( const Vector3& v1, const Vector3& v2 );
inline Vector3 operator /( const Vector3& v, const float f );

inline Vector3 operator +=( Vector3& v1, const Vector3& v2 );
inline Vector3 operator -=( Vector3& v1, const Vector3& v2 );
inline Vector3 operator *=( Vector3& v, float f );
inline Vector3 operator *=( Vector3& v1, const Vector3& v2 );
inline Vector3 operator /=( Vector3& v, float f );


/*
	Functions.
*/

inline Vector3 normalise( const Vector3& v );
inline float dot( const Vector3& v1, const Vector3& v2 );
inline float length( const Vector3& v );
inline Vector3 cross( const Vector3& v1, const Vector3& v2 );
inline Vector3 rotateVectorBy( Vector3 direction, Vector3 to_rotate, Vector3 up = Vector3( 0.0f, 1.0f, 0.0f ) );


/*
	--------------------------------
	Implementation.
*/

#include "MathUtility.hpp"

inline Vector3::Vector3()
{
}

inline Vector3::Vector3( const float X, const float Y, const float Z ):
	x(X),
	y(Y),
	z(Z)
{
}

inline Vector3& Vector3::operator =( const Vector3& v )
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

inline Vector3 Vector3::Zero()
{
	return Vector3( 0.0f, 0.0f, 0.0f );
}

inline Vector3 Vector3::RandomUnit()
{
	const float z = Fnd::Math::Randfloat( -1.0f, 1.0f );

	const float theta = Fnd::Math::Tau<float>() * Fnd::Math::Randfloat( 0.0f, 1.0f );
	
	const float d = sqrt( 1.0f - z * z );
	
	return Vector3(	
		d * cos( theta ),
		d * sin( theta ),
		z );
}

inline Vector3 Vector3::RandomDirection( const Vector3& direction, float angle_variation_radians )
{
	const float min_z = cos( angle_variation_radians );

	const float z =  Fnd::Math::Randfloat( min_z, 1.0f );
	
	const float theta = Fnd::Math::Tau<float>() * Fnd::Math::Randfloat( 0.0f, 1.0f );

	const float d = sqrt( 1.0f - z * z );

	const Vector3 rand_vec(	d * cos( theta ),
							d * sin( theta ),
							z );

	return rotateVectorBy( direction, rand_vec, Vector3( 0, 1, 0 ) );
}

inline Vector3 operator +( const Vector3& v )
{
    return v;
}

inline Vector3 operator -( const Vector3& v )
{
    return Vector3( -v.x, -v.y, -v.z );
}

inline Vector3 operator +( const Vector3& v1, const Vector3& v2 )
{
    return Vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z );
}

inline Vector3 operator -( const Vector3& v1, const Vector3& v2 )
{
    return Vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
}

inline Vector3 operator *( const float f, const Vector3& v )
{
    return Vector3( v.x * f, v.y * f, v.z * f );
}

inline Vector3 operator *( const Vector3& v, const float f )
{
    return Vector3( v.x * f, v.y * f, v.z * f );
}

inline Vector3 operator *( const Vector3& v1, const Vector3& v2 )
{
	return Vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z );
}

inline Vector3 operator /( const Vector3& v, const float f )
{
    return Vector3( v.x / f, v.y / f, v.z / f );
}

inline Vector3 operator +=( Vector3& v1, const Vector3& v2 )
{
    return v1 = Vector3( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z  );
}

inline Vector3 operator -=( Vector3& v1, const Vector3& v2 )
{
    return v1 = Vector3( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z );
}

inline Vector3 operator *=( Vector3& v, float f )
{
    return v = Vector3( v.x * f, v.y * f, v.z * f );
}

inline Vector3 operator *=( Vector3& v1, const Vector3& v2 )
{
	return v1 = Vector3( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z );
}

inline Vector3 operator /=( Vector3& v, float f )
{
    return v = Vector3( v.x / f, v.y / f, v.z / f );
}

inline Vector3 normalise( const Vector3& v )
{
	return v / length( v );
}

inline float dot( const Vector3& v1, const Vector3& v2 )
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

inline float length( const Vector3& v )
{
    return sqrt( v.x * v.x + v.y * v.y + v.z * v.z );
}

inline Vector3 cross( const Vector3& v1, const Vector3& v2 )
{
  return Vector3(	v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x );
}

inline Vector3 rotateVectorBy( Vector3 direction, Vector3 to_rotate, Vector3 up )
{
	const Vector3 w( direction );
	const Vector3 u( cross( up, w ) );
	const Vector3 v( cross( u, w ) );
				
	// 3x3 matrix multiplication
	return Vector3(	to_rotate.x * u.x + to_rotate.y * v.x + to_rotate.z * w.x,
					to_rotate.x * u.y + to_rotate.y * v.y + to_rotate.z * w.y,
					to_rotate.x * u.x + to_rotate.y * v.x + to_rotate.z * w.x );
}

}
}

#endif