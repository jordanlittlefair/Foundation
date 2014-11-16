#pragma once

#ifndef _IPHYSICS_HPP_
#define _IPHYSICS_HPP_

#include <vector>
#include <memory>
#include "../../Math/Include/Vector3.hpp"

namespace Fnd
{
namespace EntitySystem
{
class System;
}
namespace GameComponentInterfaces
{
class IPhysicsMessageListener;
}
}


namespace Fnd
{
namespace GameComponentInterfaces
{

class IPhysics
{
	public:

	virtual void SetPhysicsMessageListener( IPhysicsMessageListener* game ) = 0;

	virtual bool Initialise() = 0;

	/**
		Get a vector of systems implemented by the graphics component.
		Must be uninitialised and in order of execution.
	*/
	virtual std::vector<std::shared_ptr<Fnd::EntitySystem::System>> GetSystems() = 0;

	virtual void SetGravity( const Fnd::Math::Vector3& gravity ) = 0;

	virtual ~IPhysics() {};
};

}
}

#endif