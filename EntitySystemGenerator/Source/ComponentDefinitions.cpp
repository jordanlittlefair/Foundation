#include "../Include/ComponentDefinitions.hpp"

#include "../../Utility/Include/XmlManager.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;
using namespace Fnd::Utility;

bool ComponentDefinitions::Load( const std::string& filename )
{
	XmlManager xml_manager;
	if ( !xml_manager.CreateFromFile( filename ) )
	{
		std::cout << "Failed to load \"" << filename << "\"." << std::endl;
		return false;
	}

	rapidxml::xml_node<>* root = xml_manager.Xml().first_node("Components");

	if ( !root )
	{
		std::cout << "Failed to find root node <Components>." << std::endl;
		return false;
	}

	rapidxml::xml_node<>* component_iter = root->first_node();

	while ( component_iter )
	{
		ComponentDefinition component_definition;

		component_definition.component_name = component_iter->name();

		rapidxml::xml_node<>* data_iter = component_iter->first_node();

		while ( data_iter )
		{
			ComponentDefinition::ComponentData data;

			data.data_name = data_iter->name();

			rapidxml::xml_attribute<>* type_attrib = data_iter->first_attribute("type");
			if ( !type_attrib )
			{
				std::cout << "Component <" << component_definition.component_name << ">, Data <" << data_iter->name() << "> has no \"type\" attribute." << std::endl;
				return false;
			}
			else
			{
				data.data_type = type_attrib->value();
			}

			rapidxml::xml_attribute<>* is_required_attrib = data_iter->first_attribute("is_required");
			if ( !is_required_attrib )
			{
				data.is_required = true;
			}
			else
			{
				data.is_required = std::string( is_required_attrib->value() ) == "true";
			}

			rapidxml::xml_attribute<>* default_value_attrib = data_iter->first_attribute("default_value");
			if ( !default_value_attrib )
			{
				if ( !data.is_required )
				{
					std::cout << "Component <" << component_definition.component_name << ">, Data <" << data_iter->name() << "> is not required but has no \"default_value\" attribute." << std::endl;
					return false;
				}
				else
				{
					data.default_value = "";
				}
			}
			else
			{
				data.default_value = default_value_attrib->value();
			}

			component_definition.data.push_back(data);

			data_iter = data_iter->next_sibling();
		}

		_components.push_back( component_definition );

		component_iter = component_iter->next_sibling();
	}

	return true;
}

unsigned int ComponentDefinitions::GetNumComponents() const
{
	return _components.size();
}

const ComponentDefinitions::ComponentDefinition& ComponentDefinitions::GetComponentDefinition( unsigned int i ) const
{
	return _components[i];
}