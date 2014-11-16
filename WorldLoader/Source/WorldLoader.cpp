#include "../Include/WorldLoader.hpp"

#include "../Include/WorldDataTags.hpp"

#include "../../EntitySystem/Include/EntitySystem.hpp"
#include "../../EntitySystem/Include/Entity.hpp"
#include "../../GameComponentInterfaces/Include/IWorld.hpp"
#include "../../Utility/Include/XmlManager.hpp"

#include "../../Logger/Include/Logger.hpp"

#include <iostream>

using namespace Fnd::WorldLoader;
using namespace Fnd::GameComponentInterfaces;
using namespace Fnd::Logger;

bool WorldLoader::LoadWorld( const std::string& directory, const std::string& filename, Fnd::GameComponentInterfaces::WorldData& loaded_world_data )
{
	Logger::Logger::GetInstance().Log( Logger::LogMessage( "Loading world file: " + directory + filename ));
	
	Fnd::Utility::XmlManager xml_manager;

	bool success = xml_manager.CreateFromFile( directory + filename );

	if ( !success )
	{
		Logger::Logger::GetInstance().Log( Logger::LogError( "Failed to load world file: " + directory + filename + "; failed to parse xml" ) );
		return false;
	}

	/*
		Find the world
	*/
	rapidxml::xml_node<>* xml_world_node = xml_manager.Xml().first_node(WORLD_TAG);

	if ( !xml_world_node )
	{
		Logger::Logger::GetInstance().Log( LogMessage( "Failed to load world file: " + directory + filename + "; failed to find world node" ) );
		return false;
	}
	
	/*
		Find the entities node
	*/
	rapidxml::xml_node<>* xml_entities_node = xml_world_node->first_node(ENTITIES_TAG);

	if ( !xml_entities_node )
	{
		Logger::Logger::GetInstance().Log( LogError( "Failed to load world file: " + directory + filename + "; failed to find World::Entities node" ) );
		return false;
	}

	/*
		For each entity node, create an entity struct.
	*/
	rapidxml::xml_node<>* xml_entity_iter = xml_entities_node->first_node();

	while ( xml_entity_iter )
	{
		if ( std::string( xml_entity_iter->name() ) == ENTITY_TAG )
		{
			loaded_world_data.entities.push_back(WorldData::Entity());

			WorldData::Entity& entity = loaded_world_data.entities.back();

			auto entity_name_attrib = xml_entity_iter->first_attribute("name");
			if ( entity_name_attrib )
			{
				entity.name = entity_name_attrib->value();
			}

			auto xml_component_iter = xml_entity_iter->first_node("Components")->first_node();
			while ( xml_component_iter )
			{
				entity.components.push_back(WorldData::Entity::Component());

				WorldData::Entity::Component& component = entity.components.back();
				
				component.name = xml_component_iter->name();

				auto xml_component_data_iter = xml_component_iter->first_node();

				while ( xml_component_data_iter )
				{
					WorldData::Entity::Component::Data new_data;

					new_data.value = xml_component_data_iter->name();
					
					auto xml_data_value = xml_component_data_iter->first_attribute("value");
					if ( xml_data_value )
					{
						new_data.value = xml_data_value->value();
					}

					component.data[xml_component_data_iter->name()] = new_data;

					xml_component_data_iter = xml_component_data_iter->next_sibling();
				}

				xml_component_iter = xml_component_iter->next_sibling();
			}

			auto xml_node_iter = xml_entity_iter->first_node("Nodes")->first_node();
			while ( xml_node_iter )
			{
				entity.nodes.push_back(WorldData::Entity::Node());

				WorldData::Entity::Node& node = entity.nodes.back();

				node.name = xml_node_iter->name();

				xml_node_iter = xml_node_iter->next_sibling();
			}

			auto xml_script_iter = xml_entity_iter->first_node("Scripts")->first_node();
			while ( xml_script_iter )
			{
				entity.scripts.push_back(WorldData::Entity::Script());

				WorldData::Entity::Script& script = entity.scripts.back();

				script.name = xml_script_iter->name();

				auto xml_script_var_iter = xml_script_iter->first_attribute();
				while ( xml_script_var_iter )
				{
					script.variables[xml_script_var_iter->name()] = xml_script_var_iter->value();

					xml_script_var_iter = xml_script_var_iter->next_attribute();
				}

				xml_script_iter = xml_script_iter->next_sibling();
			}
		}
		else
		{
			return false;
		}

		xml_entity_iter = xml_entity_iter->next_sibling();
	}

	Logger::Logger::GetInstance().Log( LogMessage( "Loaded world file" ) );

	return true;
}