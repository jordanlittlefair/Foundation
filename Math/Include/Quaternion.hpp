#pragma once

#ifndef _QUATERNION_HPP_
#define _QUATERNION_HPP_

#include <cmath>
#include "Vector3.hpp"

namespace Fnd
{
namespace Math
{

struct Quaternion
{
	float x;
	float y;
	float z;
	float w;

	inline Quaternion()
	{
	}

	inline Quaternion( float x_, float y_, float z_, float w_ ):
		x(x_),
		y(y_),
		z(z_),
		w(w_)
	{
	}

	inline Quaternion( const Vector3& axis, float angle ):
		x( axis.x * sin( angle * 0.5f ) ),
		y( axis.y * sin( angle * 0.5f ) ),
		z( axis.z * sin( angle * 0.5f ) ),
		w( cos( angle * 0.5f ) )
	{
	}

	inline float GetMagnitude() const
	{
		return sqrt( x*x + y*y + z*z + w*w );
	}

	inline Quaternion GetNormalised() const
	{
		float magnitude = GetMagnitude();

		return Quaternion( x/magnitude, y/magnitude, z/magnitude, w/magnitude );
	}

	inline void Normalise()
	{
		*this = GetNormalised();
	}

	/*
		http://nic-gamedev.blogspot.co.uk/2011/11/quaternion-math-getting-local-axis.html
	*/

	inline Vector3 GetXAxis() const
	{
		return Vector3(
			1 - 2 * ( y * y + z * z ),
			2 * ( x * y + w * z ),
			2 * ( x * z - w * y ) );
	}

	inline Vector3 GetYAxis() const
	{
		return Vector3(
			2 * ( x * y - w * z ),
			1 - 2 * ( x * x + z * z ),
			2 * ( y * z + w * x ) );
	}

	inline Vector3 GetZAxis() const
	{
		return Vector3(
			2 * ( x * z + w * y ),
			2 * ( y * z - w * x ),
			1 - 2 * ( x * x + y * y ) );
	}
};

inline Quaternion operator *( const Quaternion& q1, const Quaternion& q2 )
{
	return Quaternion(
		q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
		q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
		q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w,
		q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z );
}

inline Quaternion& operator *= ( Quaternion& q1, const Quaternion& q2 )
{
	return q1 = ( q1 * q2 );
}

}
}

#endif