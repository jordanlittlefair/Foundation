#include "../Include/RigidBodySystem.hpp"

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>
#include "../Include/BulletPhysics.hpp"
#include "../Include/BulletHelper.hpp"
#include "../../Logger/Include/Logger.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"

using namespace Fnd::BulletPhysics;
using namespace Fnd::Logger;

RigidBodySystem::RigidBody::RigidBody(	btCollisionShape* collider_,
						btDefaultMotionState* motion_state_,
						btRigidBody* rigid_body_ ):
	collider(collider_),
	motion_state(motion_state_),
	rigid_body(rigid_body_)
{
}

RigidBodySystem::RigidBody::~RigidBody()
{
	if ( collider )
	{
		delete collider;
	}
	if ( motion_state )
	{
		delete motion_state;
	}
	if ( rigid_body )
	{
		delete rigid_body;
	}
}

RigidBodySystem::RigidBodySystem( BulletPhysics* physics ):
	BulletPhysicsSystem("RigidBodySystem",physics)
{
}

std::vector<std::string> RigidBodySystem::GetRegisteredNodes()
{
	std::vector<std::string> ret;

	ret.push_back("RigidBodyNode");

	return ret;
}

void RigidBodySystem::AddNode( Fnd::EntitySystem::SystemNode* node )
{
	Fnd::EntitySystem::RigidBodyNode* rigidbodynode = (Fnd::EntitySystem::RigidBodyNode*)node;

	Fnd::EntitySystem::RigidBodyNode::Pointers rigid_body_components;
	if ( !rigidbodynode->GetPointers( GetEntitySystem(), rigid_body_components ) )
	{
		return;
	}

	btCollisionShape* collider = nullptr;

	switch (rigid_body_components.rigidbody->data.collider_type)
	{
		case RIGIDBODYCOLLIDERTYPE_UNDEFINED:
			assert(0);
			break;
		case RIGIDBODYCOLLIDERTYPE_INFINITEPLANE:
			collider = new btStaticPlaneShape( btVector3( 0, 1, 0 ), 0 );
			break;
		case RIGIDBODYCOLLIDERTYPE_PLANE:
			assert(0);
			break;
		case RIGIDBODYCOLLIDERTYPE_SPHERE:
			collider = new btSphereShape( 0.5f );
			break;
		case RIGIDBODYCOLLIDERTYPE_CUBE:
			collider = new btBoxShape( btVector3( 0.5f, 0.5f, 0.5f ) );
			break;
		case RIGIDBODYCOLLIDERTYPE_MESH:
			assert(0);
			break;

		default:
			break;
	}

	if ( !collider )
	{
		return;
	}

	btVector3 initial_linear_velocity = BulletHelper::ToBullet( rigid_body_components.rigidbody->data.velocity );
	btVector3 initial_angular_velocity = BulletHelper::ToBullet( rigid_body_components.rigidbody->data.angular_velocity );
	float mass = rigid_body_components.rigidbody->data.is_static ? 
					0 :
					rigid_body_components.rigidbody->data.mass;
	float restitution = rigid_body_components.rigidbody->data.restitution;
	float friction = rigid_body_components.rigidbody->data.friction;


	btVector3 inertia;
	collider->calculateLocalInertia( mass, inertia );
		
	btTransform initial_transform;
	initial_transform.setOrigin( BulletHelper::ToBullet( rigid_body_components.scenenode->data.position ) );
	initial_transform.setRotation( BulletHelper::ToBullet( rigid_body_components.scenenode->data.rotation.GetNormalised() ) );

	btDefaultMotionState* motion_state = new btDefaultMotionState();
		
	btRigidBody::btRigidBodyConstructionInfo rigid_body_info(
		mass,
		motion_state,
		collider,
		inertia );

	rigid_body_info.m_restitution = restitution;
	rigid_body_info.m_friction = friction;

	btRigidBody* rigid_body = new btRigidBody( rigid_body_info );
	rigid_body->setCenterOfMassTransform( btTransform( btMatrix3x3(BulletHelper::ToBullet(rigid_body_components.scenenode->data.rotation.GetNormalised())),BulletHelper::ToBullet(rigid_body_components.scenenode->data.position) ) );
	rigid_body->setLinearVelocity( initial_linear_velocity );
	rigid_body->setAngularVelocity( initial_angular_velocity );
	rigid_body->setActivationState(DISABLE_DEACTIVATION);
	//rigid_body->setCollisionFlags( rigid_body_components.rigidbody->data.can_collide ? 1 : 0 );
	GetPhysics()->GetWorld()->addRigidBody(rigid_body);

	if ( !rigid_body_components.rigidbody->data.uses_gravity )
	{
		rigid_body->setGravity( btVector3(0,0,0) );
	}

	_rigid_bodies[rigidbodynode->GetRigidBodyComponentId()] = std::unique_ptr<RigidBody>( new RigidBody( collider, motion_state, rigid_body ) );
}

bool RigidBodySystem::Initialise()
{
	return true;
}

void RigidBodySystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	GetPhysics()->GetWorld()->stepSimulation( frame_data.dt, 10 );
	GetPhysics()->GetWorld()->synchronizeMotionStates();

	auto& rigid_body_nodes = GetEntitySystem().GetSystemNodesContainer().GetNodeMap<Fnd::EntitySystem::RigidBodyNode>();

	for ( auto rigid_body_iter = rigid_body_nodes.begin(); rigid_body_iter != rigid_body_nodes.end(); ++ rigid_body_iter )
	{
		Fnd::EntitySystem::RigidBodyNode::Pointers rigid_body_components;
		if ( !rigid_body_iter->second.GetPointers( GetEntitySystem(), rigid_body_components ) )
		{
			continue;
		}
		auto& rigid_body = _rigid_bodies[rigid_body_iter->second.GetRigidBodyComponentId()];
		btTransform xform;
		rigid_body->rigid_body->getMotionState()->getWorldTransform(xform);
		
		auto new_pos = xform.getOrigin();
		auto new_rot = xform.getRotation();

		rigid_body->rigid_body->setDamping( 0.5f, 0.5f );
		rigid_body->rigid_body->applyDamping(0.016f);
		
		rigid_body_components.scenenode->data.position = BulletHelper::ToFnd( new_pos );
		rigid_body_components.scenenode->data.rotation = BulletHelper::ToFnd( new_rot.normalized() );

		rigid_body->rigid_body->applyCentralImpulse( BulletHelper::ToBullet( rigid_body_components.rigidbody->data.linear_impulse ) );
		rigid_body->rigid_body->applyTorqueImpulse( BulletHelper::ToBullet( rigid_body_components.rigidbody->data.angular_impulse ) );
	}
}