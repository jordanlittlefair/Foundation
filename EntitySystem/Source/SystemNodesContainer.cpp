/*
	This file is automatically generated.
	Do not edit this file manually.
*/

#include "../Include/SystemNodesContainer.hpp"
#include "../Include/EntitySystem.hpp"
#include "../../Utility/Include/XmlManager.hpp"

using namespace Fnd::EntitySystem;

SystemNodesContainer::SystemNodesContainer( EntitySystem* entity_system ):
	_entity_system(entity_system)
{
}

SystemNode* SystemNodesContainer::CreateSystemNode( const Fnd::GameComponentInterfaces::WorldData::Entity::Node& node_data, EntitySystem& entity_system, Entity* entity )
{
	if( node_data.name == "SceneNodeNode" )
	{
		return AddSystemNode<SceneNodeNode>( entity_system, entity );
	}
	else
	if( node_data.name == "AmbientLightNode" )
	{
		return AddSystemNode<AmbientLightNode>( entity_system, entity );
	}
	else
	if( node_data.name == "CameraNode" )
	{
		return AddSystemNode<CameraNode>( entity_system, entity );
	}
	else
	if( node_data.name == "ModelNode" )
	{
		return AddSystemNode<ModelNode>( entity_system, entity );
	}
	else
	if( node_data.name == "RigidBodyNode" )
	{
		return AddSystemNode<RigidBodyNode>( entity_system, entity );
	}
	else
	if( node_data.name == "PointLightNode" )
	{
		return AddSystemNode<PointLightNode>( entity_system, entity );
	}
	else
	if( node_data.name == "DirectionalLightNode" )
	{
		return AddSystemNode<DirectionalLightNode>( entity_system, entity );
	}
	else
	if( node_data.name == "SpotLightNode" )
	{
		return AddSystemNode<SpotLightNode>( entity_system, entity );
	}
	else
	{
		return nullptr;
	}
}
