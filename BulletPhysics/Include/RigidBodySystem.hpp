#pragma once

#ifndef _BULLETPHYSICS_PHYSICSSYSTEM_HPP_
#define _BULLETPHYSICS_PHYSICSSYSTEM_HPP_

#include "BulletPhysicsSystem.hpp"
#include <memory>

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
namespace BulletPhysics
{

class RigidBodySystem:
	public Fnd::BulletPhysics::BulletPhysicsSystem
{
	public:

		RigidBodySystem( BulletPhysics* physics );

		bool Initialise();

		std::vector<std::string> GetRegisteredNodes();

		void AddNode( Fnd::EntitySystem::SystemNode* node );

	private:

		void OnUpdate( const Fnd::CommonResources::FrameData& frame_data );

		struct RigidBody
		{
			RigidBody(	btCollisionShape* collider_,
						btDefaultMotionState* motion_state_,
						btRigidBody* rigid_body_ );

			~RigidBody();

			btCollisionShape* collider;
			btDefaultMotionState* motion_state;
			btRigidBody* rigid_body;
		};

		std::map<unsigned int,std::unique_ptr<RigidBody>> _rigid_bodies;
};

}
}

#endif