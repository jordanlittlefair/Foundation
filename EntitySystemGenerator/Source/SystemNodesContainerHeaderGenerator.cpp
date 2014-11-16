#include "../Include/SystemNodesContainerHeaderGenerator.hpp"

#include <iostream>

using namespace Fnd::EntitySystemCodeGeneration;

bool SystemNodesContainerHeaderGenerator::Generate(	const SystemNodeDefinitions& systemnodes_definition,
						const std::string& output_file )
{
	SetFilename( output_file );

	WriteComment();

	WriteHeaderGuardStart();

	AddInclude( "SystemNodes.hpp" );
	AddInclude( "../../Utility/Include/IdGenerator.hpp" );
	AddInclude( "../../GameComponentInterfaces/Include/IWorld.hpp" );
	AddInclude( "EntitySystem.hpp" );
	WriteIncludeFiles();

	File() << "#include <list>\n";
	File() << "#include <map>\n\n";
	File() << "namespace Fnd\n{\nnamespace EntitySystem\n{\n\n";

	File() << "class SystemNodesContainer\n";
	File() << "{\n";
	File() << "\tpublic:\n\n";

	File() << "\tSystemNodesContainer( EntitySystem* entity_system );\n\n";

	File() << "\ttemplate <typename NodeType>\n";
	File() << "\tinline NodeType* AddSystemNode( EntitySystem& entity_system, Entity* entity );\n\n";

	File() << "\tSystemNode* CreateSystemNode( const Fnd::GameComponentInterfaces::WorldData::Entity::Node& node_data, EntitySystem& entity_system, Entity* entity );\n\n";

	File() << "\ttemplate <typename NodeType>\n";
	File() << "\tinline std::map<unsigned int,NodeType>& GetNodeMap();\n\n";

	File() << "\ttemplate <typename NodeType>\n";
	File() << "\tinline const std::map<unsigned int,NodeType>& GetNodeMap() const;\n\n";

	File() << "\ttemplate <typename NodeType>\n";
	File() << "\tinline bool RemoveSystemNode( NodeType* node );\n\n";

	/*
		For each systemnode node, create a get method code.
	*/
	/*for ( unsigned int i = 0; i < systemnodes_definition.GetNumSystemNodes(); ++i )
	{
		if ( !CreateGetMethodCode( systemnodes_definition.GetSystemNodeDefinition(i) ) )
		{
			return false;
		}
	}*/
		
	File() << "\tprivate:\n\n";

	File() << "\tEntitySystem* _entity_system;\n\n";

	/*
		For each systemnode node, create a list variable.
	*/
	for ( unsigned int i = 0; i < systemnodes_definition.GetNumSystemNodes(); ++i )
	{
		if ( !CreateVariableCode( systemnodes_definition.GetSystemNodeDefinition(i) ) )
		{
			return false;
		}
	}

	File() << "\n\tFnd::Utility::IdGenerator _id_generator;\n\n";
	
	File() << "};\n\n";


	File() << "}\n}\n\n";

	File() << "namespace Fnd\n{\nnamespace EntitySystem\n{\n\n";

	File() << "/*\n\tGetNodeMap<> implementations.\n*/\n\n";

	for ( unsigned int i = 0; i < systemnodes_definition.GetNumSystemNodes(); ++i )
	{
		if ( !CreateGetNodeMapSpecialisationCode( systemnodes_definition.GetSystemNodeDefinition(i) ) )
		{
			return false;
		}
	}

	File() << "/*\n\tAddSystemNode<> implementations.\n*/\n\n";

	for ( unsigned int i = 0; i < systemnodes_definition.GetNumSystemNodes(); ++i )
	{
		if ( !CreateAddSystemNodeSpecialisationCode( systemnodes_definition.GetSystemNodeDefinition(i) ) )
		{
			return false;
		}
	}

	File() << "/*\n\tRemoveSystemNode<> implementations.\n*/\n\n";

	for ( unsigned int i = 0; i < systemnodes_definition.GetNumSystemNodes(); ++i )
	{
		if ( !CreateRemoveSystemNodeSpecialisationCode( systemnodes_definition.GetSystemNodeDefinition(i) ) )
		{
			return false;
		}
	}

	File() << "}\n}\n\n";

	WriteHeaderGuardEnd();

	return CodeGenerator::WriteToFile();
}

bool SystemNodesContainerHeaderGenerator::CreateGetMethodCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition )
{
	File() << "\tstd::map<unsigned int," << systemnode_definition.node_name << ">& Get" << systemnode_definition.node_name << "Map();\n";
	File() << "\tconst std::map<unsigned int," << systemnode_definition.node_name << ">& Get" << systemnode_definition.node_name << "Map() const;\n\n";
	
	return true;
}

bool SystemNodesContainerHeaderGenerator::CreateVariableCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition )
{
	std::string systemnode_str = systemnode_definition.node_name;
	std::string systemnode_lower;
	for ( unsigned int i = 0; i < systemnode_str.length(); ++i )
	{
		systemnode_lower += tolower(systemnode_str[i]);
	}

	File() << "\tstd::map<unsigned int," << systemnode_definition.node_name << "> _" << systemnode_lower << ";\n";

	return true;
}

bool SystemNodesContainerHeaderGenerator::CreateGetNodeMapSpecialisationCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition )
{
	std::string systemnode_str = systemnode_definition.node_name;
	std::string systemnode_lower;
	for ( unsigned int i = 0; i < systemnode_str.length(); ++i )
	{
		systemnode_lower += tolower(systemnode_str[i]);
	}

	File() << "template <>\n";
	File() << "inline std::map<unsigned int," << systemnode_definition.node_name << ">& SystemNodesContainer::GetNodeMap<" << systemnode_definition.node_name << ">()\n";
	File() << "{\n";

	File() << "\treturn _" << systemnode_lower << ";\n";

	File() << "}\n\n";

	File() << "template <>\n";
	File() << "inline const std::map<unsigned int," << systemnode_definition.node_name << ">& SystemNodesContainer::GetNodeMap<" << systemnode_definition.node_name << ">() const\n";
	File() << "{\n";

	File() << "\treturn _" << systemnode_lower << ";\n";

	File() << "}\n\n";

	return true;
}


bool SystemNodesContainerHeaderGenerator::CreateAddSystemNodeSpecialisationCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition )
{
	std::string systemnode_str = systemnode_definition.node_name;
	std::string systemnode_lower;
	for ( unsigned int i = 0; i < systemnode_str.length(); ++i )
	{
		systemnode_lower += tolower(systemnode_str[i]);
	}
	
	File() << "template <>\n";
	File() << "inline " << systemnode_definition.node_name << "* SystemNodesContainer::AddSystemNode<" << systemnode_definition.node_name << ">( EntitySystem& entity_system, Entity* entity )\n";
	File() << "{\n";

	File() << "\t" << systemnode_definition.node_name << " node;\n";

	File() << "\tif ( node.Create( entity ) )\n";
	File() << "\t{\n";
	File() << "\t\tunsigned int id = _id_generator.GetId();\n";
	File() << "\t\t_" << systemnode_lower << "[id] = node;\n";
	File() << "\t\t_" << systemnode_lower << "[id].SetIndex(id);\n";
	File() << "\t\t_entity_system->OnAddSystemNode(&_" << systemnode_lower << "[id]);\n";
	File() << "\t\treturn &(_" << systemnode_lower << "[id]);\n";
	File() << "\t}\n";
	File() << "\telse\n";
	File() << "\t{\n";
	File() << "\t\treturn nullptr;\n";
	File() << "\t}\n";

	File() << "}\n\n";

	return true;
}

bool SystemNodesContainerHeaderGenerator::CreateRemoveSystemNodeSpecialisationCode( const SystemNodeDefinitions::SystemNodeDefinition& systemnode_definition )
{
	std::string systemnode_str = systemnode_definition.node_name;
	std::string systemnode_lower;
	for ( unsigned int i = 0; i < systemnode_str.length(); ++i )
	{
		systemnode_lower += tolower(systemnode_str[i]);
	}
	
	File() << "template <>\n";
	File() << "inline bool SystemNodesContainer::RemoveSystemNode<" << systemnode_definition.node_name << ">( " << systemnode_definition.node_name << "* node )\n";
	File() << "{\n";

	File() << "\tfor ( auto iter = _" << systemnode_lower << ".begin(); iter != _" << systemnode_lower << ".end(); ++iter )\n";
	File() << "\t{\n";
	File() << "\t\tif ( &iter->second == node )\n";
	File() << "\t\t{\n";
	File() << "\t\t\t_" << systemnode_lower << ".erase(iter);\n";
	File() << "\t\t\treturn true;\n";
	File() << "\t\t}\n";
	File() << "\t}\n";
	File() << "\treturn false;\n";

	File() << "}\n\n";

	return true;
}