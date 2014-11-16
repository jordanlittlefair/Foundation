#include "../Include/SystemNodeDefinitions.hpp"

#include "../../Utility/Include/XmlManager.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;
using namespace Fnd::Utility;

bool SystemNodeDefinitions::Load( const std::string& filename )
{
	XmlManager xml_manager;
	if ( !xml_manager.CreateFromFile( filename ) )
	{
		std::cout << "Failed to load \"" << filename << "\"." << std::endl;
		return false;
	}

	rapidxml::xml_node<>* root = xml_manager.Xml().first_node("SystemNodes");

	if ( !root )
	{
		std::cout << "Failed to find root node <SystemNodes>." << std::endl;
		return false;
	}

	rapidxml::xml_node<>* systemnode_iter = root->first_node();

	while ( systemnode_iter )
	{
		SystemNodeDefinition systemnode_definition;

		systemnode_definition.node_name = systemnode_iter->name();

		rapidxml::xml_node<>* component_iter = systemnode_iter->first_node();

		while ( component_iter )
		{
			SystemNodeDefinition::NodeComponent component;

			component.component_name = component_iter->name();

			systemnode_definition.components.push_back( component );

			component_iter = component_iter->next_sibling();
		}

		_nodes.push_back( systemnode_definition );

		systemnode_iter = systemnode_iter->next_sibling();
	}

	return true;
}

unsigned int SystemNodeDefinitions::GetNumSystemNodes() const
{
	return _nodes.size();
}

const SystemNodeDefinitions::SystemNodeDefinition& SystemNodeDefinitions::GetSystemNodeDefinition( unsigned int i ) const
{
	return _nodes[i];
}