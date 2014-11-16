#include "../Include/LoadedWorld.hpp"

#include "../../GameComponentInterfaces/Include/IWorldMessageListener.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../WorldLoader/Include/WorldLoader.hpp"
#include "../../AssetManager/Include/AssetManager.hpp"
#include "../../Utility/Include/FileSystem.hpp"
#include "../../Scripting/Include/ScriptManager.hpp"
#include "../../EntitySystem/Include/Components.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../EntitySystem/Include/ComponentMaps.hpp"
#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/EntityContainer.hpp"
#include "../../EntitySystem/Include/SystemNodes.hpp"
#include "../../EntitySystem/Include/SystemNodesContainer.hpp"

using namespace Fnd::LoadedWorld;

LoadedWorld::LoadedWorld():
	_game(nullptr)
{
}

void LoadedWorld::SetWorldMessageListener( Fnd::GameComponentInterfaces::IWorldMessageListener* game )
{
	_game = game;
}

void LoadedWorld::SetWorldSetupData( const Fnd::Setup::WorldSetupData& world_setup_data )
{
	assert( world_setup_data.world_files.find(0) != world_setup_data.world_files.end() );
	
	_world_setup_data = world_setup_data;
}

bool LoadedWorld::Initialise()
{
	if ( !_game )
	{
		return false;
	}

	unsigned int x = ~0;

	Fnd::GameComponentInterfaces::WorldData data;

	/*
		Load world with index '0'
	*/
	auto& worldfile = _world_setup_data.world_files[0];
	std::string directory;
	std::string filename;
	Fnd::Utility::FileSystem::GetPathAndName( worldfile.world_filename, directory, filename );
	Fnd::WorldLoader::WorldLoader::LoadWorld( directory, filename, data );

	/*
		Load the assets
	*/
	for ( unsigned int i = 0; i < worldfile.asset_files.size(); ++i )
	{
		_game->GetAssetManager().LoadAssets( worldfile.asset_files[i] );
	}

	/*
		Create Entities and Components
	*/
	for ( unsigned int i = 0; i < data.entities.size(); ++i )
	{
		Fnd::EntitySystem::Entity* new_entity = _game->GetEntitySystem().GetEntityContainer().CreateEntity();

		new_entity->SetName( data.entities[i].name );

		for ( unsigned int j = 0; j < data.entities[i].components.size(); ++j )
		{
			Fnd::EntitySystem::Component* new_component = _game->GetEntitySystem().GetComponentMaps().CreateComponent( data.entities[i].components[j], _game->GetEntitySystem(), x );

			// CreateComponent will eventually return a Component*, making this 'GetComponent' redundant.
			if ( new_component )
			{
				//new_component->SetIndex(new_component.component_index);
				new_entity->AddComponent(new_component);
				//component->SetOwningEntity(new_entity->GetId());
			}
		}

		for ( unsigned int j = 0; j < data.entities[i].nodes.size(); ++j )
		{
			if ( !_game->GetEntitySystem().GetSystemNodesContainer().CreateSystemNode( data.entities[i].nodes[j], _game->GetEntitySystem(), new_entity ) )
			{
				auto a = 0;
			}
		}
	}

	auto& es = _game->GetEntitySystem();
	auto& am = _game->GetAssetManager();

	/*	
		Set the model component ids - now handled in AssetLinkerSystem
	*/
	/*auto& model_components = es.GetComponentMap<Fnd::EntitySystem::ModelComponent>();
	for ( auto iter = model_components.begin(); iter != model_components.end(); ++iter )
	{
		iter->second.data.model_id = am.GetAssetByName(iter->second.data.model_asset_name);

		auto m = am.GetModel(iter->second.data.model_id);
		m->GetName();
	}*/

	auto& sm = _game->GetScriptManager();
	for ( unsigned int i = 0; i < data.entities.size(); ++i )
	{
		for ( unsigned int j = 0; j < data.entities[i].scripts.size(); ++j )
		{
			sm.AddScript( i /* TODO: this will only work when the entity index == id */, data.entities[i].scripts[j].name );
		}
	}
	
	return true;
}

LoadedWorld::~LoadedWorld()
{
}