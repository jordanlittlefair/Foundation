#include "../Include/BulletPhysics.hpp"

#include "../Include/RigidBodySystem.hpp"

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

#include "../Include/BulletHelper.hpp"

using namespace Fnd::BulletPhysics;

BulletPhysics::BulletPhysics():
	_game(nullptr)
{
}

void BulletPhysics::SetPhysicsMessageListener( Fnd::GameComponentInterfaces::IPhysicsMessageListener* game )
{
	_game = game;
}

bool BulletPhysics::Initialise()
{
	if ( !_game )
	{
		return false;
	}

	_broadphase.reset( new btDbvtBroadphase() );
	
	_collision_configuration.reset( new btDefaultCollisionConfiguration() );
	_collision_dispatcher.reset( new btCollisionDispatcher( _collision_configuration.get() ) );
	
	btGImpactCollisionAlgorithm::registerAlgorithm( _collision_dispatcher.get() );

	_solver.reset( new btSequentialImpulseConstraintSolver() );

	_dynamics_world.reset( new btDiscreteDynamicsWorld( _collision_dispatcher.get(), _broadphase.get(), _solver.get(), _collision_configuration.get() ) );

	_dynamics_world->setGravity(btVector3(0, -9.81f, 0));

	return true;
}

std::vector<std::shared_ptr<Fnd::EntitySystem::System>> BulletPhysics::GetSystems()
{
	auto systems = std::vector<std::shared_ptr<Fnd::EntitySystem::System>>();

	systems.push_back( std::shared_ptr<RigidBodySystem>( new RigidBodySystem(this) ) );
	
	return systems;
}

void BulletPhysics::SetGravity( const Fnd::Math::Vector3& gravity )
{
	_dynamics_world->setGravity( BulletHelper::ToBullet( gravity ) );
}

btDiscreteDynamicsWorld* BulletPhysics::GetWorld()
{
	return _dynamics_world.get();
}

BulletPhysics::~BulletPhysics()
{
}