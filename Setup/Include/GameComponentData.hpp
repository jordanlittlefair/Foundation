#pragma once

#ifndef _GAMECOMPONENTDATA_HPP_
#define _GAMECOMPONENTDATA_HPP_

#include <string>
#include <map>
#include <vector>

namespace rapidxml
{
	template<class Ch>
	class xml_node;
};

namespace Fnd
{
namespace Setup
{

/**
	A struct to store the data required to initialise a logger.
*/
struct LoggerSetupData
{
	std::vector<std::string> loggers;
	std::string server;
	std::string port;
};

/**
	Create a LoggerSetupData struct from a string.
	@param data_str The data as stored in an xml node.
	@return Returns a LoggerData struct containing the data from the xml node.
*/
LoggerSetupData CreateLoggerSetupData( const std::string& directory, rapidxml::xml_node<char>* logger_node );

/**
	A struct to store the data required to initialise a window.
*/
struct WindowSetupData
{
	std::string window;
	std::string window_title;
	unsigned int initial_width;
	unsigned int initial_height;
	bool is_resizable;
	bool is_fullscreen;
};

/**
	Create a WindowSetupData struct from a string.
	@param window_node The data as stored in an xml node.
	@return Returns a WindowData struct containing the data from the xml node.
*/
WindowSetupData CreateWindowSetupData( const std::string& directory, rapidxml::xml_node<char>* window_node );

/**
	A struct to store the data required to initialise a graphics implementation.
*/
struct GraphicsSetupData
{
	std::string graphics;

	bool enable_vr;
};

/**
	Create a WindowSetupData struct from a string.
	@param graphics_node The data as stored in an xml node.
	@return Returns a WindowData struct containing the data from the xml node.
*/
GraphicsSetupData CreateGraphicsSetupData( const std::string& directory, rapidxml::xml_node<char>* graphics_node );

/**
	A struct to store the data required to initialise a physics implementation.
*/
struct PhysicsSetupData
{
	std::string physics;
};

/**
	Create a PhysicsSetupData struct from a string.
	@param physics_node The data as stored in an xml node.
	@return Returns a PhysicsSetupData struct containing the data from the xml node.
*/
PhysicsSetupData CreatePhysicsSetupData( const std::string& directory, rapidxml::xml_node<char>* physics_node );

/**
	A struct to store the data required to initialise a world implementation.
*/
struct WorldSetupData
{
	std::string world;

	struct WorldFile
	{
		std::string world_filename;
		std::vector<std::string> asset_files;
	};

	std::map<int,WorldFile> world_files;
	std::vector<std::string> asset_file;
};

/**
	Create a WorldSetupData struct from a string.
	@param world_node The data as stored in an xml node.
	@return Returns a WorldData struct containing the data from the xml node.
*/
WorldSetupData CreateWorldSetupData( const std::string& directory, rapidxml::xml_node<char>* world_node );

/**
	A struct to store the data required to initialise a scripting implementation.
*/
struct ScriptingSetupData
{
	std::string scripting;
};

/**
	Create a ScriptingSetupData struct from a string.
	@param scripting_node The data as stored in an xml node.
	@return Returns a ScriptingSetupData struct containing the data from the xml node.
*/
ScriptingSetupData CreateScriptingSetupData( const std::string& directory, rapidxml::xml_node<char>* scripting_node );

}
}

#endif