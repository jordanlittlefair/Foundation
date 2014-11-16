#pragma once

#ifndef _BULLETHELPER_HPP_
#define _BULLETHELPER_HPP_

#include <btBulletDynamicsCommon.h>
#include "../../Math/Include/Math.hpp"

namespace Fnd
{
namespace BulletPhysics
{

class BulletHelper
{
	public:

		static inline btVector3 ToBullet( const Fnd::Math::Vector3& v )
		{
			return btVector3( v.x, v.y, v.z );
		}

		static inline btQuaternion ToBullet( const Fnd::Math::Quaternion& q )
		{
			return btQuaternion( q.x, q.y, q.z, q.w );
		}

		static inline Fnd::Math::Vector3 ToFnd( const btVector3& v )
		{
			return Fnd::Math::Vector3( v.x(), v.y(), v.z() );
		}

		static inline Fnd::Math::Quaternion ToFnd( const btQuaternion& q )
		{
			return Fnd::Math::Quaternion( q.x(), q.y(), q.z(), q.w() ).GetNormalised();
		}
};

}
}
#endif