#include "../Include/ApplicationSettingsReader.hpp"

#include "../../Utility/Include/XmlManager.hpp"

using namespace Fnd::Launcher;
using namespace Fnd::Utility;

std::string ApplicationSettingsReader::GetEngineDirectory( const std::string& filename )
{
	XmlManager xml_manager;

	if ( !xml_manager.CreateFromFile( filename ) )
	{
		return "";
	}

	auto root_node = xml_manager.Xml().first_node( "GameSetup" );

	if ( !root_node )
	{
		return "";
	}

	auto engine_node = root_node->first_node( "Engine" );

	if ( !engine_node )
	{
		return "";
	}

	auto engine_dir_attrib = engine_node->first_attribute( "directory" );

	if ( !engine_dir_attrib )
	{
		return "";
	}

	return engine_dir_attrib->value();
}