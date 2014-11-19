#pragma once

#ifndef _BULLETPHYSICS_BULLETPHYSICS_HPP_
#define _BULLETPHYSICS_BULLETPHYSICS_HPP_

#include "../../GameComponentInterfaces/Include/IPhysics.hpp"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class btCollisionShape;
struct btDefaultMotionState;

namespace Fnd
{
namespace GameComponentInterfaces
{
class IPhysicsMessageListener;
}
}

namespace Fnd
{
namespace BulletPhysics
{

class BulletPhysics:
	public Fnd::GameComponentInterfaces::IPhysics
{
	public:

		BulletPhysics();

		void SetPhysicsMessageListener( Fnd::GameComponentInterfaces::IPhysicsMessageListener* game );

		bool Initialise();

		std::vector<std::shared_ptr<Fnd::EntitySystem::System>> GetSystems();

		void SetGravity( const Fnd::Math::Vector3& gravity );

		~BulletPhysics();

		/*
			Below: could be added to an interface
		*/

		btDiscreteDynamicsWorld* GetWorld();

	private:

		Fnd::GameComponentInterfaces::IPhysicsMessageListener* _game;

		std::unique_ptr<btBroadphaseInterface> _broadphase;
		std::unique_ptr<btDefaultCollisionConfiguration> _collision_configuration;
		std::unique_ptr<btCollisionDispatcher> _collision_dispatcher;
		std::unique_ptr<btSequentialImpulseConstraintSolver> _solver;
		std::unique_ptr<btDiscreteDynamicsWorld> _dynamics_world;
};

}
}

#endif