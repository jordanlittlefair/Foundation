#include "../Include/SystemNodesSourceGenerator.hpp"

#include "../../Utility/Include/XmlManager.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;

bool SystemNodesSourceGenerator::Generate(	const SystemNodeDefinitions& systemnode_definitions,
						const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();

	AddInclude( "../Include/Components.hpp" );
	AddInclude( "../Include/EntitySystem.hpp" );
	AddInclude( "../Include/SystemNodes.hpp" );
	AddInclude( "../Include/Components.hpp" );
	AddInclude( "../Include/Entity.hpp" );
	AddInclude( "../Include/ComponentMaps.hpp" );
	AddInclude( "../Include/EntitySystem.hpp" );
	AddInclude( "../Include/EntityContainer.hpp" );
	AddInclude( "../Include/SystemNodes.hpp" );
	AddInclude( "../Include/SystemNodesContainer.hpp" );

	WriteIncludeFiles();

	File() << "using namespace Fnd::EntitySystem;\n\n";

	/*
		For each systemnode, create systemnode code.
	*/
		for ( unsigned int i = 0; i < systemnode_definitions.GetNumSystemNodes(); ++i )
		{
			if ( !CreateSystemNodeCode( systemnode_definitions.GetSystemNodeDefinition(i) ) )
			{
				return false;
			}
		}

	return CodeGenerator::WriteToFile();
}

bool SystemNodesSourceGenerator::CreateSystemNodeCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definitions )
{
	File() << "" << systemnode_definitions.node_name << "::" << systemnode_definitions.node_name << "()";

	File() << ":\n\tSystemNode(\"" << systemnode_definitions.node_name << "\")";

	if ( !systemnode_definitions.components.empty() )
	{
		File() << ",";
	}
	File() << "\n";

	File() << "\t_entity_id(InvalidComponentIndex)" << ( systemnode_definitions.components.empty() ? "" : "," ) << "\n";

	for ( unsigned int i = 0; i < systemnode_definitions.components.size(); ++i )
	{
		std::string component_str = systemnode_definitions.components[i].component_name;
		std::string component_lower;
		for ( unsigned int j = 0; j < component_str.length(); ++j )
		{
			component_lower += tolower(component_str[j]);
		}

		auto component_start = component_lower.find("component");
		if ( component_start != std::string::npos )
		{
			component_lower = component_lower.substr( 0, component_start );
		}

		File() << "\t_" << component_lower << "_id(InvalidComponentIndex)";

		if ( i + 1 < systemnode_definitions.components.size() )
		{
			File() << ",";
		}
		File() << "\n";
	}
	
	File() << "{\n";
	File() << "}\n\n";

	File() << "bool " << systemnode_definitions.node_name << "::Create( Entity* entity )\n";
	File() << "{\n";
	{
		File() << "\t_entity_id = entity->GetId();\n\n";

		for ( unsigned int i = 0; i < systemnode_definitions.components.size(); ++i )
		{
			std::string component_str = systemnode_definitions.components[i].component_name;
			std::string component_lower;
			for ( unsigned int j = 0; j < component_str.length(); ++j )
			{
				component_lower += tolower(component_str[j]);
			}

			auto component_start = component_lower.find("component");
			if ( component_start != std::string::npos )
			{
				component_lower = component_lower.substr( 0, component_start );
			}

			File() << "\t_" << component_lower << "_id = entity->GetComponentId<" << systemnode_definitions.components[i].component_name << ">();\n";

			File() << "\tif ( _" << component_lower << "_id == InvalidComponentIndex )\n";
			File() << "\t{\n";
			File() << "\t\treturn false;\n";
			File() << "\t}\n\n";
		}
	}
	File() << "\treturn true;\n";
	File() << "}\n\n";

	File() << "bool " << systemnode_definitions.node_name << "::GetPointers( EntitySystem& entity_system, Pointers& pointers )\n";
	File() << "{\n";
	File() << "\tPointers p;\n\n";

	File() << "\tif ( !entity_system.GetEntityContainer().GetEntity(_entity_id) )\n";
	File() << "\t{\n\t\treturn false;\n\t}\n\n";

	{
		for ( unsigned int i = 0; i < systemnode_definitions.components.size(); ++i )
		{
			std::string component_str = systemnode_definitions.components[i].component_name;
			std::string component_lower;
			for ( unsigned int j = 0; j < component_str.length(); ++j )
			{
				component_lower += tolower(component_str[j]);
			}

			auto component_start = component_lower.find("component");
			if ( component_start != std::string::npos )
			{
				component_lower = component_lower.substr( 0, component_start );
			}

			File() << "\tp." << component_lower << " = entity_system.GetComponentMaps().GetComponent<" << systemnode_definitions.components[i].component_name << ">( _" << component_lower << "_id );\n";
			File() << "\tif ( p." << component_lower << " == nullptr )\n";
			File() << "\t{\n";
			File() << "\t\treturn false;\n";
			File() << "\t}\n\n";
		}
	}
	File() << "\tpointers = p;\n";
	File() << "\treturn true;\n";
	File() << "}\n\n";

	File() << "unsigned int " << systemnode_definitions.node_name << "::GetEntityId()\n";
	File() << "{\n\treturn _entity_id;\n}\n\n";

	{
		for ( unsigned int i = 0; i < systemnode_definitions.components.size(); ++i )
		{
			File() << "unsigned int " << systemnode_definitions.node_name << "::Get" << systemnode_definitions.components[i].component_name << "Id() const\n{\n";

			std::string component_str = systemnode_definitions.components[i].component_name;
			std::string component_lower;
			for ( unsigned int j = 0; j < component_str.length(); ++j )
			{
				component_lower += tolower(component_str[j]);
			}

			auto component_start = component_lower.find("component");
			if ( component_start != std::string::npos )
			{
				component_lower = component_lower.substr( 0, component_start );
			}

			File() << "\treturn _" << component_lower << "_id;\n}\n\n";
		}
	}

	return true;
}