#include "../Include/SystemNodesContainerSourceGenerator.hpp"

#include "../../Utility/Include/XmlManager.hpp"

#include <iostream>
//bool AddSystemNode( const Fnd::GameComponentInterfaces::WorldData::Entity::Node& node, Entity* entity );
using namespace Fnd::EntitySystemCodeGeneration;

bool SystemNodesContainerSourceGenerator::Generate(	const SystemNodeDefinitions& systemnodes_definition,
						const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();
	
	AddInclude( "../Include/SystemNodesContainer.hpp" );
	AddInclude( "../Include/EntitySystem.hpp" );
	AddInclude( "../../Utility/Include/XmlManager.hpp" );

	WriteIncludeFiles();

	File() << "using namespace Fnd::EntitySystem;\n\n";

	/*
		For each systemnode node, create a get method code.
	*/
	/*for ( unsigned int i = 0; i < systemnodes_definition.GetNumSystemNodes(); ++i )
	{
		if ( !CreateSystemNodeCode( systemnodes_definition.GetSystemNodeDefinition(i) ) )
		{
			return false;
		}
	}*/

	File() << "SystemNodesContainer::SystemNodesContainer( EntitySystem* entity_system ):\n";
	File() << "\t_entity_system(entity_system)\n";
	File() << "{\n";
	File() << "}\n\n";

	File() << "SystemNode* SystemNodesContainer::CreateSystemNode( const Fnd::GameComponentInterfaces::WorldData::Entity::Node& node_data, EntitySystem& entity_system, Entity* entity )\n";
	File() << "{\n";
	
	for ( unsigned int i = 0; i < systemnodes_definition.GetNumSystemNodes(); ++i )
	{
		File() << "\tif( node_data.name == \"" << systemnodes_definition.GetSystemNodeDefinition(i).node_name << "\" )\n";
		File() << "\t{\n";
		File() << "\t\treturn AddSystemNode<" << systemnodes_definition.GetSystemNodeDefinition(i).node_name << ">( entity_system, entity );\n";
		File() << "\t}\n";
		File() << "\telse\n";
	}

	File() << "\t{\n";
	File() << "\t\treturn nullptr;\n";
	File() << "\t}\n";
	File() << "}\n";

	return CodeGenerator::WriteToFile();
}

bool SystemNodesContainerSourceGenerator::CreateSystemNodeCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition )
{
	std::string systemnode_str = systemnode_definition.node_name;
	std::string systemnode_lower;
	for ( unsigned int i = 0; i < systemnode_str.length(); ++i )
	{
		systemnode_lower += tolower(systemnode_str[i]);
	}

	File() << "std::map<unsigned int," << systemnode_definition.node_name << ">& SystemNodesContainer::Get" << systemnode_definition.node_name << "Map()\n";
	File() << "{\n";
	File() << "\treturn _" << systemnode_lower << ";\n";
	File() << "}\n\n";

	File() << "const std::map<unsigned int," << systemnode_definition.node_name << ">& SystemNodesContainer::Get" << systemnode_definition.node_name << "Map() const\n";
	File() << "{\n";
	File() << "\treturn _" << systemnode_lower << ";\n";
	File() << "}\n\n";

	return true;
}

