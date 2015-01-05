#include "../Include/AssetLinkerSystem.hpp"

#include "../../EntitySystem/Include/Components.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"

using namespace Fnd::GameSystems;
using namespace Fnd::EntitySystem;

AssetLinkerSystem::AssetLinkerSystem():
	Fnd::EntitySystem::System("AssetLinkerSystem")
{
}

std::vector<std::string> AssetLinkerSystem::GetRegisteredNodes()
{
	std::vector<std::string> ret;

	ret.push_back("ModelNode");

	return ret;
}

bool AssetLinkerSystem::Initialise()
{
	return true;
}

void AssetLinkerSystem::AddNode( SystemNode* node )
{
	if ( node->GetName() == "ModelNode" )
	{
		auto modelnode = (ModelNode*)node;


		ModelNode::Pointers model_components;
		if ( !modelnode->GetPointers( GetEntitySystem(), model_components ) )
		{
			return;
		}

		model_components.model->data.model_id = GetAssetManager().GetAssetByName( model_components.model->data.model_asset_name );
	}
}

void AssetLinkerSystem::OnUpdate( const Fnd::CommonResources::FrameData& frame_data )
{
	
}