#include "../Include/BulletPhysicsSystem.hpp"

using namespace Fnd::BulletPhysics;

BulletPhysicsSystem::BulletPhysicsSystem( const std::string& system_name, BulletPhysics* physics ):
	_physics(physics),
	System(system_name)
{
}

BulletPhysics* BulletPhysicsSystem::GetPhysics()
{
	return _physics;
}