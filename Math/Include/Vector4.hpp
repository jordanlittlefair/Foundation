#pragma once

#ifndef _MATH_VECTOR4_
#define _MATH_VECTOR4_

namespace Fnd
{
namespace Math
{

/*
	4D Vector.
*/
struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	inline Vector4();
    inline Vector4( float X, float Y, float Z, float W );
	inline Vector4& operator =( const Vector4& v );

	inline static Vector4 Zero();
};


/*
	Operators.
*/

inline Vector4 operator +( const Vector4& v );
inline Vector4 operator -( const Vector4& v );
inline Vector4 operator +( const Vector4& v1, const Vector4& v2 );
inline Vector4 operator -( const Vector4& v1, const Vector4& v2 );
inline Vector4 operator *( const float f, const Vector4& v );
inline Vector4 operator *( const Vector4& v, const float f );
inline Vector4 operator *( const Vector4& v1, const Vector4& v2 );
inline Vector4 operator /( const Vector4& v, const float f );

inline Vector4 operator +=( Vector4& v1, const Vector4& v2 );
inline Vector4 operator -=( Vector4& v1, const Vector4& v2 );
inline Vector4 operator *=( Vector4& v, float f );
inline Vector4 operator *=( Vector4& v1, const Vector4& v2 );
inline Vector4 operator /=( Vector4& v, float f );


/*
	--------------------------------
	Implementation
*/

inline Vector4::Vector4()
{
}

inline Vector4::Vector4( float X, float Y, float Z, float W ):
	x(X), 
	y(Y), 
	z(Z), 
	w(W)
{
}

inline Vector4& Vector4::operator =( const Vector4& v )
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;

	return *this;
}

inline Vector4 Vector4::Zero()
{
	return Vector4( 0.0f, 0.0f, 0.0f, 0.0f );
}

inline Vector4 operator +( const Vector4& v )
{
    return v;
}

inline Vector4 operator -( const Vector4& v )
{
    return Vector4( -v.x, -v.y, -v.z, -v.w );
}

inline Vector4 operator +( const Vector4& v1, const Vector4& v2 )
{
    return Vector4( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w );
}

inline Vector4 operator -( const Vector4& v1, const Vector4& v2 )
{
    return Vector4( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w );
}

inline Vector4 operator *( const float f, const Vector4& v )
{
    return Vector4( v.x * f, v.y * f, v.z * f, v.w * f );
}

inline Vector4 operator *( const Vector4& v, const float f )
{
    return Vector4( v.x * f, v.y * f, v.z * f, v.w * f );
}

inline Vector4 operator *( const Vector4& v1, const Vector4& v2 )
{
	return Vector4( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w );
}

inline Vector4 operator /( const Vector4& v, const float f )
{
    return Vector4( v.x / f, v.y / f, v.z / f, v.w / f );
}

inline Vector4 operator +=( Vector4& v1, const Vector4& v2 )
{
    return v1 = Vector4( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w );
}

inline Vector4 operator -=( Vector4& v1, const Vector4& v2 )
{
    return v1 = Vector4( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w );
}

inline Vector4 operator *=( Vector4& v, float f )
{
    return v = Vector4( v.x * f, v.y * f, v.z * f, v.w * f );
}

inline Vector4 operator *=( Vector4& v1, const Vector4& v2 )
{
	return v1 = Vector4( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w );
}

inline Vector4 operator /=( Vector4& v, float f )
{
    return v = Vector4( v.x / f, v.y / f, v.z / f, v.w / f );
}

}
}

#endif