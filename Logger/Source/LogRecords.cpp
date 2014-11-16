#include "../Include/LogRecords.hpp"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "../../Setup/Include/GameComponentData.hpp"

using namespace Fnd::Logger;

std::string Fnd::Logger::ParseLogSessionIdJson( const std::string& json )
{
	std::string ret;

	try
	{
		std::stringstream ss;
		ss << json;

		boost::property_tree::ptree tree;
		boost::property_tree::json_parser::read_json( ss, tree );

		ret = tree.get<std::string>("logSessionId");

	}
	catch ( std::exception& e )
	{
		(void)e;
	}

	return ret;
}

std::string Fnd::Logger::WriteWindowSetupDataJson( const Fnd::Setup::WindowSetupData& window_data )
{
	std::string ret;

	try
	{
		boost::property_tree::ptree tree;

		tree.put( "windowData.implementation", window_data.window );
		tree.put( "windowData.windowTitle", window_data.window_title );
		tree.put( "windowData.initialWidth", window_data.initial_width );
		tree.put( "windowData.initialHeight", window_data.initial_height );
		tree.put( "windowData.isResizable", window_data.is_resizable );
		tree.put( "windowData.isFullscreen", window_data.is_fullscreen );

		std::stringstream ss;
		boost::property_tree::json_parser::write_json( ss, tree, false );
		
		ret = ss.str();
	}
	catch ( std::exception& e )
	{
		(void)e;
	}

	return ret;
}

std::string Fnd::Logger::WriteGraphicsSetupDataJson( const Fnd::Setup::GraphicsSetupData& graphics_data )
{
	std::string ret;

	try
	{
		boost::property_tree::ptree tree;

		tree.put( "graphicsData.implementation", graphics_data.graphics );

		std::stringstream ss;
		boost::property_tree::json_parser::write_json( ss, tree, false );
		
		ret = ss.str();
	}
	catch ( std::exception& e )
	{
		(void)e;
	}

	return ret;
}

std::string Fnd::Logger::WriteWorldSetupDataJson( const Fnd::Setup::WorldSetupData& world_data )
{
	std::string ret;

	try
	{
		boost::property_tree::ptree tree;

		tree.put( "worldData.implementation", world_data.world );

		boost::property_tree::ptree world_file_array;

		for ( auto iter = world_data.world_files.begin(); iter != world_data.world_files.end(); ++iter )
		{
			boost::property_tree::ptree element;
			std::stringstream level_index_ss; level_index_ss << iter->first;
			auto s = level_index_ss.str();
			element.put( level_index_ss.str(), iter->second.world_filename );

			world_file_array.push_back( std::make_pair( "", element ) );
		}

		tree.add_child( "worldData.worldFiles", world_file_array );

		std::stringstream ss;
		boost::property_tree::json_parser::write_json( ss, tree, false );
		
		ret = ss.str();
	}
	catch ( std::exception& e )
	{
		(void)e;
	}

	return ret;
}

std::string Fnd::Logger::WriteLogMessageJson( const LogMessage& log_message, unsigned int time )
{
	std::string ret;

	try
	{
		boost::property_tree::ptree tree;

		tree.put( "type", "message" );
		tree.put( "time", time );
		tree.put( "message", log_message.message );

		std::stringstream ss;
		boost::property_tree::json_parser::write_json( ss, tree, false );
		
		ret = ss.str();
	}
	catch ( std::exception& e )
	{
		(void)e;
	}

	return ret;
}

std::string Fnd::Logger::WriteLogErrorJson( const LogError& log_error, unsigned int time )
{
	std::string ret;

	try
	{
		boost::property_tree::ptree tree;

		tree.put( "type", "error" );
		tree.put( "time", time );
		tree.put( "message", log_error.message );

		std::stringstream ss;
		boost::property_tree::json_parser::write_json( ss, tree, false );
		
		ret = ss.str();
	}
	catch ( std::exception& e )
	{
		(void)e;
	}

	return ret;
}

std::string Fnd::Logger::WriteLogWarningJson( const LogWarning& log_warning, unsigned int time )
{
	std::string ret;

	try
	{
		boost::property_tree::ptree tree;

		tree.put( "type", "warning" );
		tree.put( "time", time );
		tree.put( "message", log_warning.message );

		std::stringstream ss;
		boost::property_tree::json_parser::write_json( ss, tree, false );
		
		ret = ss.str();
	}
	catch ( std::exception& e )
	{
		(void)e;
	}

	return ret;
}