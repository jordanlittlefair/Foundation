#include "../Include/EntitySystemGeneratorConfig.hpp"

#include "../../Utility/Include/XmlManager.hpp"

#include <iostream>

using namespace Fnd::EntitySystemGenerator;
using namespace Fnd::Utility;

bool EntitySystemGeneratorConfig::LoadConfigFile( const std::string& directory, const std::string& filename )
{
	_directories = Directories();

	Fnd::Utility::XmlManager xml_manager;
	xml_manager.CreateFromFile( directory + filename );
	
	/*
		Find the Components (root) tag.
	*/
	rapidxml::xml_node<>* root_node = xml_manager.Xml().first_node("Config");

	if ( !root_node )
	{
		std::cout << "Error: Cannot find <Config> node.\n";
		return false;
	}

	auto directories_node = root_node->first_node("Directories");

	if ( !directories_node ) 
	{
		std::cout << "Error: Cannot find <Directories> node.\n";
		return false;
	}

	auto input_attrib = directories_node->first_attribute("input_directory");

	if ( !input_attrib )
	{
		std::cout << "Error: Cannot find \"input_directory\" attrib.\n";
		return false;
	}

	_directories.input = directory + input_attrib->value();

	auto output_attrib = directories_node->first_attribute("output_directory");

	if ( !output_attrib )
	{
		std::cout << "Error: Cannot find \"output_directory\" attrib.\n";
		return false;
	}

	_directories.output = directory + output_attrib->value();

	return true;
}

EntitySystemGeneratorConfig::Directories EntitySystemGeneratorConfig::GetDirectories()
{
	return _directories;
}