#pragma once

#ifndef _VECTOR2_
#define _VECTOR2_

namespace Fnd
{
namespace Math
{

/*
	2D Vector.
*/ 
struct Vector2
{
	float x;
	float y;

	inline Vector2();
	inline Vector2( const float X, const float Y );
	inline Vector2& operator =( const Vector2& v );

	inline static Vector2 Zero();
};


/*
	Operators.
*/

inline Vector2 operator +( const Vector2& v );
inline Vector2 operator -( const Vector2& v );
inline Vector2 operator +( const Vector2& v1, const Vector2& v2 );
inline Vector2 operator -( const Vector2& v1, const Vector2& v2 );
inline Vector2 operator *( const float f, const Vector2& v );
inline Vector2 operator *( const Vector2& v, const float f );
inline Vector2 operator *( const Vector2& v1, const Vector2& v2 );
inline Vector2 operator /( const Vector2& v, const float f );

inline Vector2 operator +=( Vector2& v1, const Vector2& v2 );
inline Vector2 operator -=( Vector2& v1, const Vector2& v2 );
inline Vector2 operator *=( Vector2& v, float f );
inline Vector2 operator *=( Vector2& v1, const Vector2& v2 );
inline Vector2 operator /=( Vector2& v, float f );


/*
	Functions.
*/

// Return a normalised Vector of v.
inline Vector2 normalise( const Vector2& v );

// Returns the dot product of Vectors v1 and v2.
inline float dot( const Vector2& v1, const Vector2& v2 );

// Returns the length of Vector v.
inline float length( const Vector2& v );

// Returns the length of Vector v squared.
// Useful for comparing Vector lengths without calling sqrt.
inline float lengthSquared( const Vector2& v );


/*
	----------------------------------------------------------------
	Implementation.
*/

#include "MathUtility.hpp"

inline Vector2::Vector2()
{
}

inline Vector2::Vector2( const float X, const float Y ):
	x(X),
	y(Y)
{
}

inline Vector2& Vector2::operator =( const Vector2& v )
{
	x = v.x;
	y = v.y;

	return *this;
}

inline Vector2 Vector2::Zero()
{
	return Vector2( 0.0f, 0.0f );
}

inline Vector2 operator +( const Vector2& v )
{
	return v;
}

inline Vector2 operator -( const Vector2& v )
{
	return Vector2( -v.x, -v.y );
}

inline Vector2 operator +( const Vector2& v1, const Vector2& v2 )
{
	return Vector2( v1.x + v2.x, v1.y + v2.y );
}

inline Vector2 operator -( const Vector2& v1, const Vector2& v2 )
{
	return Vector2( v1.x - v2.x, v1.y - v2.y );
}

inline Vector2 operator *( const float f, const Vector2& v )
{
	return Vector2( f * v.x, f* v.y );
}

inline Vector2 operator *( const Vector2& v, const float f )
{
	return Vector2( v.x * f, v.y * f );
}


inline Vector2 operator *( const Vector2& v1, const Vector2& v2 )
{
	return Vector2( v1.x * v2.x, v1.y * v2.y );
}

inline Vector2 operator /( const Vector2& v, const float f )
{
	return Vector2( v.x / f, v.y / f );
}

inline Vector2 operator +=( Vector2& v1, const Vector2& v2 )
{
	return v1 = Vector2( v1.x + v2.x, v1.y + v2.y );
}

inline Vector2 operator -=( Vector2& v1, const Vector2& v2 )
{
	return v1 = Vector2( v1.x - v2.x, v1.y - v2.y );
}

inline Vector2 operator *=( Vector2& v, float f )
{
	return v = Vector2( v.x * f, v.y * f );
}

inline Vector2 operator *=( Vector2& v1, const Vector2& v2 )
{
	return v1 = Vector2( v1.x * v2.x, v1.y * v2.y );
}

inline Vector2 operator /=( Vector2& v, float f )
{
	return v = Vector2( v.x / f, v.y / f );
}

inline Vector2 normalise( const Vector2& v )
{
	return v / length( v );
}

inline float dot( const Vector2& v1, const Vector2& v2 )
{
	 return v1.x * v2.x + v1.y * v2.y;
}

inline float length( const Vector2& v )
{
	return sqrt( v.x * v.x + v.y * v.y );
}

inline float lengthSquared( const Vector2& v )
{
	return v.x * v.x + v.y * v.y;
}

}
}

#endif