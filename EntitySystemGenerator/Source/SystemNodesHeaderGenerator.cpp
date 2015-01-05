#include "../Include/SystemNodesHeaderGenerator.hpp"

#include "../Include/ComponentDefinitionTags.hpp"

#include "../../Utility/Include/XmlManager.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;

bool SystemNodesHeaderGenerator::Generate(	const SystemNodeDefinitions& systemnode_definitions,
						const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();

	WriteHeaderGuardStart();

	AddInclude( "Components.hpp" );
	AddInclude( "SystemNode.hpp" );

	WriteIncludeFiles();

	File() << "namespace Fnd\n{\nnamespace EntitySystem\n{\n\n";

	File() << "class EntitySystem;\n\n";

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

	File() << "}\n}\n\n";
	
	WriteHeaderGuardEnd();

	return CodeGenerator::WriteToFile();
}

bool SystemNodesHeaderGenerator::CreateSystemNodeCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition )
{
	File() << "class " << systemnode_definition.node_name << ":\n";
	File() << "\tpublic Fnd::EntitySystem::SystemNode\n";
	File() << "{\n";
	File() << "\tpublic:\n\n";

	File() << "\t\tstruct Pointers\n";
	File() << "\t\t{\n";
	
	for ( unsigned int i = 0; i < systemnode_definition.components.size(); ++i )
	{
		std::string component_str = systemnode_definition.components[i].component_name;
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

		File() << "\t\t\t" << systemnode_definition.components[i].component_name << "* " << component_lower << ";\n";
	}

	File() << "\t\t};\n\n";

	File() << "\t\t" << systemnode_definition.node_name << "();\n\n";

	File() << "\t\tbool Create( Entity* entity );\n\n";

	File() << "\t\tbool GetPointers( EntitySystem& entity_system, Pointers& pointers );\n\n";

	File() << "\t\tunsigned int GetEntityId();\n\n";

	for ( unsigned int i = 0; i < systemnode_definition.components.size(); ++i )
	{
		File() << "\t\tunsigned int Get" << systemnode_definition.components[i].component_name << "Id() const;\n\n";
	}

	File() << "\tprivate:\n\n";

	File() << "\t\tunsigned int _entity_id;\n\n";

	
	for ( unsigned int i = 0; i < systemnode_definition.components.size(); ++i )
	{
		std::string component_str = systemnode_definition.components[i].component_name;
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

		File() << "\t\tunsigned int _" << component_lower << "_id;\n";
	}
	

	File() << "};\n\n";

	return true;
}