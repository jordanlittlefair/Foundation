#pragma once

#ifndef _MATHUTILITY_
#define _MATHUTILITY_

#include <cmath>
#include <cstdlib>

namespace Fnd
{
namespace Math
{

/**
	Get pi cast to the templated type.
	@return Returns pi.
*/
template <typename T>
inline T Pi()
{
	return (T)3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170;
}

/**
	Get tau (2pi) cast to the templated type.
	@return Returns tau.
*/
template <typename T>
inline T Tau()
{
	return (T)6.2831853071795864769252867665590057683943387987502116419498891846156328125724179972560696506842341;
}

/*
	Utility functions.
*/

/**
	Get a random float.
	@param min The minimum value.
	@param max The maximum value.
	@return Returns random value between min and max.
*/
inline float Randfloat( const float min, const float max );

/**
	Convert degrees to radians.
	@param degrees The angle in degrees.
	@return Returns the angle in radians.
*/
inline float ToRadians( const float degrees );

/**
	Convert radians to degrees.
	@param radians The angle in radians.
	@return Returns the angle in degrees.
*/
inline float ToDegrees( const float radians );

/**
	Get the absolute value of a number.
	@param a The positive or negative value.
	@return Returns the absolute value of 'a'.
*/
template <typename T>
inline T Abs( T a );

/**
	Get the smaller of two values.
	@param a The first value to compare.
	@param b The second value to compare.
	@return Returns the smallest of 'a' and 'b'.
*/
template <typename T>
inline T Min( const T a, const T b );

/**
	Get the largest of two values.
	@param a The first value to compare.
	@param b The second value to compare.
	@return Returns the largest of 'a' and 'b'.
*/
template <typename T>
inline T Max( const T a, const T b );

/**
	Clamp a value.
	@param value The value to be clamped.
	@param minimum The smallest value which 'value' can take.
	@param maximum The largest value which 'value' can take.
	@return Returns 'value' clamped to the range 'minimum'->'maximum'.
*/
template <typename T>
inline T Clamp( const T value, const T minimum, const T maximum );

/**
	Linear interpolate between two values.
	Does not clamp the result between 'a' and 'b'.
	@param a The first value to interpolate between, where 's' = 0.
	@param b The second value to interpolate between, where 's' = 1.
	@return Returns an interpolated value.
*/
template <typename Value, typename Parameter>
inline Value Lerp( const Value a, const Value b, Parameter s );

/*
	Function definitions.
*/

inline float Randfloat( const float min, const float max )
{
	return min + ( ( (max - min) * rand() ) / (float)RAND_MAX );
}

inline float ToRadians( const float degrees )
{
	return degrees * ( Tau<float>() / 360.0f );
}

inline float ToDegrees( const float radians )
{
	return radians * ( 360.0f / Tau<float>() );
}

template <typename T>
inline T Abs( T a )
{
	return a > 0 ? a : -a;
}

template <typename T>
inline T Min( const T a, const T b )
{
	return a < b ? a : b;
}

template <typename T>
inline T Max( const T a, const T b )
{
	return a > b ? a : b;
}

template <typename T>
inline T Clamp( const T value, const T minimum, const T maximum )
{
	return Min( maximum, Max( minimum, value ) );
}

template <typename Value, typename Parameter>
inline Value Lerp( const Value a, const Value b, Parameter s )
{
	return a + ( b - a ) * s;
}

}
}

#endif
