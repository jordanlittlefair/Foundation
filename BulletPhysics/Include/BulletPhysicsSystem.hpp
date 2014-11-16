#pragma once

#ifndef _BULLETPHYSICSSYSTEM_HPP_
#define _BULLETPHYSICSSYSTEM_HPP_

#include "../../EntitySystem/Include/System.hpp"

namespace Fnd
{
namespace BulletPhysics
{
class BulletPhysics;

class BulletPhysicsSystem:
	public Fnd::EntitySystem::System
{
	public:

		BulletPhysicsSystem( const std::string& system_name, BulletPhysics* physics );

	protected:

		BulletPhysics* GetPhysics();

	private:

		BulletPhysics* _physics;
};

}
}

#endif