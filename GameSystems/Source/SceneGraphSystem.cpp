#include "../Include/SceneGraphSystem.hpp"

#include "../../Logger/Include/Logger.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"

using namespace Fnd::GameSystems;
using namespace Fnd::Math;
using namespace Fnd::Logger;
using namespace Fnd::EntitySystem;

SceneGraphSystem::GraphNode::GraphNode():
	node(nullptr)
{
}
	

void SceneGraphSystem::GraphNode::GenerateMatrices( SceneGraphSystem* system, Fnd::Math::Matrix4& xform )
{
	SceneNodeNode::Pointers components;

	if ( node->GetPointers(system->GetEntitySystem(),components) )
	{
		Vector3 model_pos = components.scenenode->data.position;
		Quaternion model_rot = components.scenenode->data.rotation.GetNormalised();
		Vector3 model_scale = components.scenenode->data.scale;

		Matrix4 scale_matrix = Matrix4Helper<>::CreateScaleMatrix( model_scale.x, model_scale.y, model_scale.z );

		Matrix4 this_matrix = (scale_matrix * Matrix4Helper<>::CreateRotationMatrix( model_rot )) * Matrix4Helper<>::CreateTranslationMatrix( model_pos );

		components.scenenode->data.transform = this_matrix * xform;

		for ( unsigned int i = 0; i < children.size(); ++i )
		{
			children[i].GenerateMatrices( system, components.scenenode->data.transform );
		}
	}
}

SceneGraphSystem::GraphNode* SceneGraphSystem::GraphNode::FindNode( unsigned int search_id )
{
	if ( entity_id == search_id )
	{
		return this;
	}
	else
	{
		for ( unsigned int i = 0; i < children.size(); ++i )
		{
			GraphNode* ret = children[i].FindNode(search_id);
			if ( ret )
			{
				return ret;
			}
		}

		return nullptr;
	}
}

SceneGraphSystem::GraphNode* SceneGraphSystem::FindNode( unsigned int search_id )
{
	for ( unsigned int i = 0; i < _parents.size(); ++i )
	{
		GraphNode* ret = _parents[i].FindNode(search_id);

		if ( ret )
		{
			return ret;
		}
	}

	return nullptr;
}

SceneGraphSystem::SceneGraphSystem():
	Fnd::EntitySystem::System("SceneGraphSystem")
{
}

std::vector<std::string> SceneGraphSystem::GetRegisteredNodes()
{
	std::vector<std::string> ret;

	ret.push_back("SceneNodeNode");

	return ret;
}

bool SceneGraphSystem::Initialise()
{
	return true;
}

void SceneGraphSystem::AddNode( SystemNode* node )
{
	if ( node->GetName() == "SceneNodeNode" )
	{
		SceneNodeNode* scenenodenode = (SceneNodeNode*)node;

		SceneNodeNode::Pointers components;

		if ( scenenodenode->GetPointers( GetEntitySystem(), components ) )
		{
			std::string parent_name = components.scenenode->data.parent_name;

			if ( !parent_name.empty() )
			{
				Entity* parent = GetEntitySystem().GetEntityContainer().GetEntityByName(parent_name);
				
				components.scenenode->data.parent_id = parent->GetId();

				auto parent_node = FindNode( parent->GetId() );

				GraphNode new_node;
				new_node.node = scenenodenode;
				new_node.entity_id = scenenodenode->GetEntityId();
				parent_node->children.push_back(new_node);
			}
			else
			{
				GraphNode new_node;
				new_node.node = scenenodenode;
				new_node.entity_id = scenenodenode->GetEntityId();
				_parents.push_back(new_node);
			}
		}
	}

}

void SceneGraphSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	/*auto& scenenode_list = GetEntitySystem().GetSystemNodesContainer().GetSceneNodeNodeMap();

	for ( auto iter = scenenode_list.begin(); iter !=scenenode_list.end(); ++iter )
	{
		Fnd::EntitySystem::SceneNodeNode::Pointers components;

		if ( iter->second.GetPointers( GetEntitySystem(), components ) )
		{
			auto& scenenode_data = components.scenenode->data;

			if ( scenenode_data.parent_id != 4294967295 )
				Logger::Logger::GetInstance().Log( LogWarning( "SceneNode [" + std::string() + "] has a parent but this is not yet handled in SceneGraphSystem." ) );

			Vector3 model_pos = scenenode_data.position;
			Quaternion model_rot = scenenode_data.rotation.GetNormalised();
			Vector3 model_scale = scenenode_data.scale;

			Matrix4 scale_matrix = Matrix4Helper<>::CreateScaleMatrix( model_scale.x, model_scale.y, model_scale.z );

			scenenode_data.transform = (scale_matrix * Matrix4Helper<>::CreateRotationMatrix( model_rot )) * Matrix4Helper<>::CreateTranslationMatrix( model_pos );
		}
	}*/

	for ( unsigned int i = 0; i < _parents.size(); ++i )
	{
		_parents[i].GenerateMatrices(this,Matrix4::Identity());
	}
}