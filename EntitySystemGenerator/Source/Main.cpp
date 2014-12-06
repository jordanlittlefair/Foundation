#include <iostream>

#include "../Include/EntitySystemGeneratorConfig.hpp"
#include "../Include/ComponentsHeaderGenerator.hpp"
#include "../Include/ComponentsSourceGenerator.hpp"
#include "../Include/ComponentCreatorSourceGenerator.hpp"
#include "../Include/ComponentMapsHeaderGenerator.hpp"
#include "../Include/ComponentMapsSourceGenerator.hpp"
#include "../Include/SystemNodesHeaderGenerator.hpp"
#include "../Include/SystemNodesSourceGenerator.hpp"
#include "../Include/SystemNodesContainerHeaderGenerator.hpp"
#include "../Include/SystemNodesContainerSourceGenerator.hpp"

#include "../Include/ComponentDefinitions.hpp"
#include "../Include/SystemNodeDefinitions.hpp"

#include "../../Utility/Include/FileSystem.hpp"

using namespace Fnd::EntitySystemCodeGeneration;
using namespace Fnd::Utility;

bool Generate( const Fnd::EntitySystemGenerator::EntitySystemGeneratorConfig::Directories& directories, const ComponentDefinitions& component_definitions, const Fnd::EntitySystemCodeGeneration::SystemNodeDefinitions& systemnode_definitions )
{
	bool success = true;

	std::cout << "Creating \"Include\" and \"Source\" directories...." << std::endl;

    FileSystem::CreateNewDirectory( directories.output + "Include" );
	
	FileSystem::CreateNewDirectory( directories.output + "Source" );

	/*
		Generate Components.hpp
	*/
	{
		std::cout << "\tGenerating \"Components.hpp\"....\n";

		ComponentsHeaderGenerator chg;
		success = chg.Generate(	component_definitions,
								directories.output + "Include\\Components.hpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"Components.hpp\"." << std::endl;
		
			return false;
		}

		std::cout << "\tGenerated  \"Components.hpp\" successfully.\n";
	}
	/*
		Generate Components.cpp
	*/
	{
		std::cout << "\tGenerating \"Components.cpp\"....\n";

		ComponentsSourceGenerator csg;

		success = csg.Generate(	component_definitions,
								directories.output + "Source\\Components.cpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"Components.cpp\"." << std::endl;

			return false;
		}

		std::cout << "\tGenerated  \"Components.cpp\" successfully.\n";
	}

	/*
		Generate ComponentCreatorSourceGenerator.cpp
	*/
	{
		std::cout << "\tGenerating \"ComponentCreator.cpp\"....\n";

		ComponentCreatorSourceGenerator ccsg;

		success = ccsg.Generate(	component_definitions,
									directories.output + "Source\\ComponentCreator.cpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"ComponentCreator.cpp\"." << std::endl;

			return false;
		}

		std::cout << "\tGenerated  \"ComponentCreator.cpp\" successfully.\n";
	}

	/*
		Generate ComponentMapsHeaderGenerator.hpp
	*/
	{
		std::cout << "\tGenerating \"ComponentMaps.hpp\"....\n";

		ComponentMapsHeaderGenerator cmhg;

		success = cmhg.Generate(	component_definitions,
									directories.output + "Include\\ComponentMaps.hpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"ComponentMaps.hpp\"." << std::endl;

			return false;
		}

		std::cout << "\tGenerated  \"ComponentMaps.hpp\" successfully.\n";
	}

	/*
		Generate ComponentMapsSourceGenerator.cpp
	*/
	{
		std::cout << "\tGenerating \"ComponentMaps.cpp\"....\n";

		ComponentMapsSourceGenerator cmsg;

		success = cmsg.Generate(	component_definitions,
									directories.output + "Source\\ComponentMaps.cpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"ComponentMaps.cpp\"." << std::endl;

			return false;
		}

		std::cout << "\tGenerated  \"ComponentMaps.cpp\" successfully.\n";
	}

	/*
		Generate SystemNodesHeaderGenerator.hpp
	*/
	{
		std::cout << "\tGenerating \"SystemNodes.hpp\"....\n";

		SystemNodesHeaderGenerator snhg;

		success = snhg.Generate(	systemnode_definitions,
									directories.output + "Include\\SystemNodes.hpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"SystemNodes.hpp\"." << std::endl;

			return false;
		}

		std::cout << "\tGenerated  \"SystemNodes.hpp\" successfully.\n";
	}

	/*
		Generate SystemNodesSourceGenerator.hpp
	*/
	{
		std::cout << "\tGenerating \"SystemNodes.cpp\"....\n";

		SystemNodesSourceGenerator snsg;

		success = snsg.Generate(	systemnode_definitions,
									directories.output + "Source\\SystemNodes.cpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"SystemNodes.cpp\"." << std::endl;

			return false;
		}

		std::cout << "\tGenerated  \"SystemNodes.cpp\" successfully.\n";
	}
	
	/*
		Generate SystemNodesContainerHeaderGenerator.hpp
	*/
	{
		std::cout << "\tGenerating \"SystemNodesContainer.hpp\"....\n";

		SystemNodesContainerHeaderGenerator snchg;

		success = snchg.Generate(	systemnode_definitions,
									directories.output + "Include\\SystemNodesContainer.hpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"SystemNodesContainer.hpp\"." << std::endl;

			return false;
		}

		std::cout << "\tGenerated  \"SystemNodesContainer.hpp\" successfully.\n";
	}

	/*
		Generate SystemNodesContainerSourceGenerator.hpp
	*/
	{
		std::cout << "\tGenerating \"SystemNodesContainer.cpp\"....\n";

		SystemNodesContainerSourceGenerator sncsg;

		success = sncsg.Generate(	systemnode_definitions,
									directories.output + "Source\\SystemNodesContainer.cpp" );

		if ( !success )
		{
			std::cout << "\tFailed to generate \"SystemNodesContainer.cpp\"." << std::endl;

			return false;
		}

		std::cout << "\tGenerated  \"SystemNodesContainer.cpp\" successfully.\n";
	}

	return true;
}

int main(int argc, char* argv[])
{
	std::cout <<	"--------------------------------\n";
	std::cout <<	"EntitySystemGenerator\n";
	std::cout <<	"--------------------------------\n";
	std::cout <<	"Generating EntitySystem code....\n";

	Fnd::EntitySystemGenerator::EntitySystemGeneratorConfig config;

	if ( !config.LoadConfigFile( "EntitySystemGenerator/", "Config.xml") )
	{
		std::cout << "Failed to load \"EntitySystemGenerator/Config.xml\"" << std::endl;
		return 0;
	}

	Fnd::EntitySystemCodeGeneration::ComponentDefinitions component_definitions;
	component_definitions.Load( config.GetDirectories().input + "ComponentDefinitions.xml" );

	Fnd::EntitySystemCodeGeneration::SystemNodeDefinitions systemnode_definitions;
	systemnode_definitions.Load( config.GetDirectories().input + "SystemNodeDefinitions.xml" );
	//return 0;
	bool success = Generate( config.GetDirectories(), component_definitions, systemnode_definitions );

	if ( success )
	{
		std::cout << "Generated EntitySystem code successfully.\n";
	}
	else
	{
		std::cout << "Failed to Generate EntitySystem code.\n";
	}

	//TODO: Destroy function- either auto generated or taken from that .xml file

	std::cout <<	"--------------------------------" << std::endl;

	system("pause");

	std::cout <<	"--------------------------------" << std::endl;

	return success ? 0 : 1;
}